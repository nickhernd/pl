#ifndef _IR_LINEARIZER_H
#define _IR_LINEARIZER_H

// [IR-7] Linearizador de Bloques
// Divide la lista plana de cuádruplas en bloques básicos y
// construye el grafo de flujo de control (CFG).
//
// Un bloque básico es una secuencia maximal de cuádruplas sin saltos
// intermedios: entrada por la primera instrucción, salida por la última.

#include "IR.h"
#include <vector>
#include <unordered_map>
#include <string>

struct BasicBlock {
    int              id;
    std::vector<IRQuad> quads;
    std::vector<int> successors;    // IDs de bloques sucesores
    std::vector<int> predecessors;  // IDs de bloques predecesores
};

class IRLinearizer {
public:
    std::vector<BasicBlock> blocks;

    // Construye los bloques básicos a partir del programa IR
    void build(const IRProgram& prog) {
        blocks.clear();
        const auto& qs = prog.quads;
        if (qs.empty()) return;

        // Paso 1: identificar líderes (primera instrucción de cada bloque)
        std::vector<bool> isLeader(qs.size(), false);
        isLeader[0] = true;

        for (int i = 0; i < (int)qs.size(); ++i) {
            IROpcode op = qs[i].op;
            if (op == IR_JMP || op == IR_JZ || op == IR_JNZ) {
                // La instrucción siguiente al salto es líder
                if (i + 1 < (int)qs.size())
                    isLeader[i + 1] = true;
            }
            if (op == IR_LABEL) {
                // El destino de etiquetas es líder
                isLeader[i] = true;
            }
        }

        // Paso 2: agrupar en bloques básicos
        BasicBlock current;
        current.id = 0;
        for (int i = 0; i < (int)qs.size(); ++i) {
            if (isLeader[i] && !current.quads.empty()) {
                blocks.push_back(current);
                current.quads.clear();
                current.id = (int)blocks.size();
            }
            current.quads.push_back(qs[i]);
        }
        if (!current.quads.empty())
            blocks.push_back(current);

        // Paso 3: construir mapa etiqueta → índice de bloque
        std::unordered_map<std::string, int> labelToBlock;
        for (int b = 0; b < (int)blocks.size(); ++b) {
            if (!blocks[b].quads.empty()) {
                const IRQuad& first = blocks[b].quads.front();
                if (first.op == IR_LABEL)
                    labelToBlock[first.arg1.name] = b;
            }
        }

        // Paso 4: conectar sucesores/predecesores
        for (int b = 0; b < (int)blocks.size(); ++b) {
            if (blocks[b].quads.empty()) continue;
            const IRQuad& last = blocks[b].quads.back();

            auto addEdge = [&](int from, int to) {
                blocks[from].successors.push_back(to);
                blocks[to].predecessors.push_back(from);
            };

            switch (last.op) {
                case IR_JMP: {
                    auto it = labelToBlock.find(last.arg1.name);
                    if (it != labelToBlock.end())
                        addEdge(b, it->second);
                    break;
                }
                case IR_JZ:
                case IR_JNZ: {
                    // Rama verdadera: etiqueta en arg2
                    auto it = labelToBlock.find(last.arg2.name);
                    if (it != labelToBlock.end())
                        addEdge(b, it->second);
                    // Rama falsa: bloque siguiente
                    if (b + 1 < (int)blocks.size())
                        addEdge(b, b + 1);
                    break;
                }
                case IR_HALT:
                case IR_RETURN:
                    break;  // sin sucesores
                default:
                    // Caída al siguiente bloque
                    if (b + 1 < (int)blocks.size())
                        addEdge(b, b + 1);
                    break;
            }
        }
    }

    // Vuelca los bloques básicos a stderr para depuración
    void dump(std::ostream& out = std::cerr) const {
        out << "=== Bloques Básicos (CFG) ===" << std::endl;
        for (const auto& bb : blocks) {
            out << "BB" << bb.id << " [pred:";
            for (int p : bb.predecessors) out << " BB" << p;
            out << "] [succ:";
            for (int s : bb.successors) out << " BB" << s;
            out << "]\n";
            for (const auto& q : bb.quads) {
                out << "    (" << q.op << ")\n";
            }
        }
        out << "=============================" << std::endl;
    }
};

#endif
