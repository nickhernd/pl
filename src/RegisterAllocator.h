#ifndef _REGISTER_ALLOCATOR_H
#define _REGISTER_ALLOCATOR_H

// [BND-13] Asignación de Registros: Algoritmo de Chaitin-Briggs simplificado
//
// Fases:
//   1. Análisis de Vivacidad (liveness analysis) por bloques básicos
//   2. Construcción del Grafo de Interferencias
//   3. Coloración del Grafo (greedy k-coloring)
//
// Registros disponibles (llamador-guarda, System V AMD64 ABI):
//   Enteros: %rcx, %rdx, %r8, %r9, %r10, %r11   (K_INT = 6)
//   Reales:  %xmm2, %xmm3, %xmm4, %xmm5, %xmm6, %xmm7  (K_REAL = 6)
//
// Variables/temporales que no obtienen registro se "derraman" (spill) a la pila.

#include "IR.h"
#include "IRLinearizer.h"
#include "TablaSimbolos.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <iostream>

// Resultado de la asignación: addr IR -> nombre de registro físico
// addr con registro "" significa spill (sigue en pila)
using RegMap = std::unordered_map<int, std::string>;

class RegisterAllocator {
public:
    // Registros físicos disponibles
    static const std::vector<std::string> INT_REGS;
    static const std::vector<std::string> REAL_REGS;

private:
    // ------------------------------------------------------------------ //
    //  Estructuras internas
    // ------------------------------------------------------------------ //

    // Información de vivacidad por bloque básico
    struct LiveInfo {
        std::unordered_set<int> use;     // addrs usadas antes de definición
        std::unordered_set<int> def;     // addrs definidas en el bloque
        std::unordered_set<int> liveIn;  // vivas a la entrada
        std::unordered_set<int> liveOut; // vivas a la salida
    };

    // Tipo de un addr IR (ENTERO=0, REAL=1)
    std::unordered_map<int, int> addrType;

    // Grafo de interferencias: addr -> conjunto de addrs que interfieren
    std::unordered_map<int, std::unordered_set<int>> graph;

    // Todos los nodos (addrs) del grafo
    std::unordered_set<int> allNodes;

    // ------------------------------------------------------------------ //
    //  Registro de tipo de cada addr
    // ------------------------------------------------------------------ //

    void collectTypes(const IRProgram& prog) {
        auto reg = [&](const IRArg& a) {
            if ((a.kind == ARG_VAR || a.kind == ARG_TEMP) && a.type >= 0)
                addrType[a.addr] = a.type;
        };
        for (const auto& q : prog.quads) {
            reg(q.arg1); reg(q.arg2); reg(q.result);
        }
    }

    // ------------------------------------------------------------------ //
    //  Fase 1: Análisis de Vivacidad
    // ------------------------------------------------------------------ //

    std::vector<LiveInfo> computeLiveness(const IRLinearizer& lin) {
        int n = (int)lin.blocks.size();
        std::vector<LiveInfo> info(n);

        // Calcula use[] y def[] para cada bloque
        for (int b = 0; b < n; ++b) {
            for (const auto& q : lin.blocks[b].quads) {
                // Los operandos usados antes de ser definidos van a use[]
                auto useArg = [&](const IRArg& a) {
                    if (a.kind == ARG_VAR || a.kind == ARG_TEMP) {
                        if (info[b].def.find(a.addr) == info[b].def.end())
                            info[b].use.insert(a.addr);
                    }
                };
                useArg(q.arg1);
                useArg(q.arg2);

                // El resultado va a def[]
                if (q.result.kind == ARG_VAR || q.result.kind == ARG_TEMP)
                    info[b].def.insert(q.result.addr);
            }
        }

        // Ecuaciones de punto fijo:
        //   liveIn[b]  = use[b] ∪ (liveOut[b] - def[b])
        //   liveOut[b] = ∪ liveIn[s]  para s en sucesores de b
        bool changed = true;
        while (changed) {
            changed = false;
            for (int b = n - 1; b >= 0; --b) {
                // liveOut = union de liveIn de sucesores
                std::unordered_set<int> newOut;
                for (int s : lin.blocks[b].successors)
                    for (int v : info[s].liveIn)
                        newOut.insert(v);

                // liveIn = use ∪ (liveOut - def)
                std::unordered_set<int> newIn = info[b].use;
                for (int v : newOut)
                    if (info[b].def.find(v) == info[b].def.end())
                        newIn.insert(v);

                if (newIn != info[b].liveIn || newOut != info[b].liveOut) {
                    info[b].liveIn  = newIn;
                    info[b].liveOut = newOut;
                    changed = true;
                }
            }
        }
        return info;
    }

    // ------------------------------------------------------------------ //
    //  Fase 2: Grafo de Interferencias
    // ------------------------------------------------------------------ //

    void addInterference(int a, int b) {
        if (a == b) return;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    void buildInterferenceGraph(const IRLinearizer& lin,
                                const std::vector<LiveInfo>& liveness) {
        for (int b = 0; b < (int)lin.blocks.size(); ++b) {
            // Simulación hacia atrás: live = liveOut del bloque
            std::unordered_set<int> live = liveness[b].liveOut;

            // Registra todos los nodos
            for (int v : live) allNodes.insert(v);
            for (int v : liveness[b].liveIn) allNodes.insert(v);

            const auto& quads = lin.blocks[b].quads;
            for (int i = (int)quads.size() - 1; i >= 0; --i) {
                const IRQuad& q = quads[i];

                // La definición interfiere con todo lo vivo en este punto
                if (q.result.kind == ARG_VAR || q.result.kind == ARG_TEMP) {
                    int d = q.result.addr;
                    allNodes.insert(d);
                    for (int v : live)
                        addInterference(d, v);
                    live.erase(d);
                }

                // Los usos se vuelven vivos
                auto addLive = [&](const IRArg& a) {
                    if (a.kind == ARG_VAR || a.kind == ARG_TEMP) {
                        allNodes.insert(a.addr);
                        live.insert(a.addr);
                    }
                };
                addLive(q.arg1);
                addLive(q.arg2);
            }
        }

        // Asegurarse de que todos los nodos existen en el grafo
        for (int v : allNodes)
            if (graph.find(v) == graph.end())
                graph[v] = {};
    }

    // ------------------------------------------------------------------ //
    //  Fase 3: Coloración del Grafo (Chaitin-Briggs simplificado)
    // ------------------------------------------------------------------ //

    RegMap colorGraph() {
        RegMap assignment;

        // Separamos nodos por tipo
        std::vector<int> intNodes, realNodes;
        for (int v : allNodes) {
            auto it = addrType.find(v);
            int t = (it != addrType.end()) ? it->second : ENTERO;
            if (t == REAL) realNodes.push_back(v);
            else           intNodes.push_back(v);
        }

        auto color = [&](std::vector<int>& nodes, const std::vector<std::string>& regs) {
            int K = (int)regs.size();
            // Copia del grafo (solo los nodos de este tipo)
            std::unordered_map<int, std::unordered_set<int>> g;
            for (int v : nodes) g[v] = {};
            for (int v : nodes)
                for (int u : graph[v])
                    if (g.find(u) != g.end())
                        g[v].insert(u);

            // Pila de simplificación y conjunto de spills
            std::stack<int> stk;
            std::unordered_set<int> spilled;
            std::unordered_set<int> removed;

            // Iteramos hasta procesar todos los nodos
            while ((int)(removed.size() + spilled.size()) < (int)nodes.size()) {
                bool progress = false;

                // Buscar nodo con grado < K para simplificar
                for (int v : nodes) {
                    if (removed.count(v) || spilled.count(v)) continue;
                    int deg = 0;
                    for (int u : g[v])
                        if (!removed.count(u) && !spilled.count(u)) ++deg;

                    if (deg < K) {
                        stk.push(v);
                        removed.insert(v);
                        progress = true;
                        break;
                    }
                }

                // Si no hay progreso, hacer spill del nodo con mayor grado
                if (!progress) {
                    int maxDeg = -1, victim = -1;
                    for (int v : nodes) {
                        if (removed.count(v) || spilled.count(v)) continue;
                        int deg = 0;
                        for (int u : g[v])
                            if (!removed.count(u) && !spilled.count(u)) ++deg;
                        if (deg > maxDeg) { maxDeg = deg; victim = v; }
                    }
                    if (victim >= 0) {
                        spilled.insert(victim);
                        assignment[victim] = "";  // spill
                    }
                }
            }

            // Selección de colores (en orden inverso de la pila)
            while (!stk.empty()) {
                int v = stk.top(); stk.pop();
                std::unordered_set<int> usedColors;
                for (int u : g[v]) {
                    auto it = assignment.find(u);
                    if (it != assignment.end() && !it->second.empty()) {
                        // encuentra índice del registro
                        for (int i = 0; i < K; ++i)
                            if (regs[i] == it->second)
                                usedColors.insert(i);
                    }
                }
                // Asigna el primer color libre
                bool assigned = false;
                for (int i = 0; i < K; ++i) {
                    if (!usedColors.count(i)) {
                        assignment[v] = regs[i];
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) assignment[v] = "";  // spill real
            }
        };

        color(intNodes,  INT_REGS);
        color(realNodes, REAL_REGS);
        return assignment;
    }

public:
    // ------------------------------------------------------------------ //
    //  Punto de entrada: realiza las 3 fases y devuelve la asignación
    // ------------------------------------------------------------------ //

    RegMap allocate(const IRProgram& prog) {
        collectTypes(prog);

        IRLinearizer lin;
        lin.build(prog);

        auto liveness = computeLiveness(lin);
        buildInterferenceGraph(lin, liveness);
        return colorGraph();
    }

    // Vuelca la asignación a stderr para depuración
    static void dump(const RegMap& rm, std::ostream& out = std::cerr) {
        out << "=== Asignación de Registros ===\n";
        for (const auto& kv : rm) {
            out << "  addr " << kv.first << " -> "
                << (kv.second.empty() ? "(spill)" : kv.second) << "\n";
        }
        out << "===============================\n";
    }
};

const std::vector<std::string> RegisterAllocator::INT_REGS  =
    {"%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"};
const std::vector<std::string> RegisterAllocator::REAL_REGS =
    {"%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7"};

#endif
