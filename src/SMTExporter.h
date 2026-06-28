#ifndef _SMT_EXPORTER_H
#define _SMT_EXPORTER_H

// [VER-8]  Exportación de VCs a SMT-Lib2 para Z3
// [VER-10] Interpretación de la salida de Z3 y reporte de errores
//
// Flujo:
//   VC formula → toSMT() → fichero .smt2 → z3 → sat/unsat → reporte
//
// UNSAT: negación insatisfacible → VC válida → programa correcto en ese punto
// SAT:   negación satisfacible  → contraejemplo → BUG

#include "VCGenerator.h"
#include "TablaSimbolos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

class SMTExporter {
    std::ostream& out;

public:
    explicit SMTExporter(std::ostream& o = std::cout) : out(o) {}

    // ------------------------------------------------------------------ //
    //  Declara todas las variables del programa como constantes SMT-Lib2
    //  Recorre la cadena de ámbitos (padre → hijo)
    // ------------------------------------------------------------------ //
    void declareVars(const TablaSimbolos* ts) {
        if (!ts) return;
        declareVars(ts->padre);
        for (const auto& s : ts->simbolos) {
            if (s.isFunction) continue;
            if (s.tipo == ENTERO)  out << "(declare-fun " << s.nombre << " () Int)\n";
            if (s.tipo == REAL)    out << "(declare-fun " << s.nombre << " () Real)\n";
            if (s.tipo == LOGICO)  out << "(declare-fun " << s.nombre << " () Bool)\n";
        }
    }

    // ------------------------------------------------------------------ //
    //  Exporta UNA VC como comprobación SMT-Lib2
    //  Negamos la fórmula: UNSAT → válida, SAT → bug
    // ------------------------------------------------------------------ //
    void exportVC(const VC& vc, const TablaSimbolos* globalTS) {
        out << "; " << vc.description << "\n";
        declareVars(globalTS);           // variables globales (funciones)
        if (vc.methodTS) declareVars(vc.methodTS);  // variables locales del método
        if (vc.formula)
            out << "(assert (not " << vc.formula->toSMT() << "))\n";
        else
            out << "(assert false)\n";
        out << "(check-sat)\n\n";
    }

    // ------------------------------------------------------------------ //
    //  Exporta TODAS las VCs en un único fichero .smt2
    //  Cada VC está aislada con (push 1) / (pop 1)
    // ------------------------------------------------------------------ //
    void exportAll(const std::vector<VC>& vcs, const TablaSimbolos* globalTS) {
        out << "; Verification Conditions — JavaSubset compiler\n";
        out << "; z3 fichero.smt2\n\n";
        for (const auto& vc : vcs) {
            out << "(push 1)\n";
            exportVC(vc, globalTS);
            out << "(pop 1)\n\n";
        }
        out << "(exit)\n";
    }

    // ------------------------------------------------------------------ //
    //  [VER-10] Ejecuta Z3 sobre el fichero y devuelve la salida completa
    // ------------------------------------------------------------------ //
    static std::string runZ3(const std::string& smtFile) {
        std::string cmd = "z3 " + smtFile + " 2>&1";
        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) return "";
        char buf[512];
        std::string result;
        while (fgets(buf, sizeof(buf), pipe))
            result += buf;
        pclose(pipe);
        return result;
    }

    // ------------------------------------------------------------------ //
    //  [VER-10] Interpreta la salida de Z3 y reporta para cada VC
    //
    //  Z3 produce una línea "unsat"/"sat"/"unknown" por cada (check-sat).
    //  Con (push)/(pop) la salida está alineada con el orden de las VCs.
    // ------------------------------------------------------------------ //
    static void reportResults(const std::string& z3output,
                               const std::vector<VC>& vcs) {
        std::istringstream stream(z3output);
        std::string line;
        size_t vcIdx = 0;
        int ok = 0, bug = 0, unk = 0;

        while (std::getline(stream, line) && vcIdx < vcs.size()) {
            if (line.empty() || line[0] == '(') continue;  // modelo/error

            const std::string& desc = vcs[vcIdx].description;
            if (line == "unsat") {
                std::cout << "  \033[32m[OK] \033[0m " << desc << "\n";
                ++ok; ++vcIdx;
            } else if (line.rfind("sat", 0) == 0) {
                std::cout << "  \033[31m[BUG]\033[0m " << desc
                          << " — contraejemplo encontrado\n";
                ++bug; ++vcIdx;
            } else if (line == "unknown") {
                std::cout << "  \033[33m[?]  \033[0m " << desc
                          << " — Z3 no pudo decidir\n";
                ++unk; ++vcIdx;
            }
            // otras líneas (errores del modelo, etc.) se ignoran
        }

        std::cout << "\n  Resultado: " << ok << " OK";
        if (bug > 0) std::cout << ", \033[31m" << bug << " BUGS\033[0m";
        if (unk > 0) std::cout << ", " << unk << " sin decidir";
        std::cout << "\n";
    }
};

#endif
