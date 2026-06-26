#ifndef _SMT_EXPORTER_H
#define _SMT_EXPORTER_H

// [VER-8] Interfaz con Z3 mediante el formato SMT-Lib2
//
// SMT-Lib2 es el estándar de entrada para solvers como Z3, CVC5, MathSAT.
// Para verificar que una VC "P ==> Q" es válida, Z3 comprueba que
// su NEGACIÓN "NOT(P ==> Q)" es INSATISFACIBLE (UNSAT).
//
// Si Z3 dice UNSAT  → la VC es válida → el programa es correcto en ese punto.
// Si Z3 dice SAT    → encontró un contraejemplo → el programa tiene un bug.
// Si Z3 dice UNKNOWN → tiempo agotado o lógica demasiado compleja.
//
// Ejemplo de salida SMT-Lib2 para VC "x > 0 ==> x + 1 > 0":
//   (declare-fun x () Int)
//   (assert (not (=> (> x 0) (> (+ x 1) 0))))
//   (check-sat)
//   (get-model)   ; solo si SAT, para ver el contraejemplo
//
// Uso:
//   z3 output.smt2        # desde terminal
//
// Instalación de Z3:
//   sudo pacman -S z3      # Arch Linux
//   sudo apt install z3    # Ubuntu/Debian

#include "VCGenerator.h"
#include "TablaSimbolos.h"
#include <iostream>
#include <string>
#include <vector>

class SMTExporter {
    std::ostream& out;

public:
    explicit SMTExporter(std::ostream& o = std::cout) : out(o) {}

    // ------------------------------------------------------------------ //
    //  Declara las variables del programa en SMT-Lib2
    //  Necesario para que Z3 conozca los tipos de cada variable
    // ------------------------------------------------------------------ //
    void declareVars(const TablaSimbolos* ts) {
        // TODO VER-8:
        // Recorre ts->simbolos y emite para cada variable:
        //   int  → (declare-fun nombre () Int)
        //   real → (declare-fun nombre () Real)
        //   bool → (declare-fun nombre () Bool)
        //
        // Ejemplo:
        //   for (const auto& s : ts->simbolos) {
        //       if (s.tipo == ENTERO)  out << "(declare-fun " << s.nombre << " () Int)\n";
        //       if (s.tipo == REAL)    out << "(declare-fun " << s.nombre << " () Real)\n";
        //       if (s.tipo == LOGICO)  out << "(declare-fun " << s.nombre << " () Bool)\n";
        //   }
    }

    // ------------------------------------------------------------------ //
    //  Exporta UNA VC a formato SMT-Lib2
    //  Para verificar validez, negamos la fórmula y pedimos SAT
    // ------------------------------------------------------------------ //
    void exportVC(const VC& vc, const TablaSimbolos* ts) {
        // TODO VER-8:
        // out << "; " << vc.description << "\n";
        // declareVars(ts);
        // out << "(assert (not " << vc.formula->toSMT() << "))\n";
        // out << "(check-sat)\n";
        // out << "(get-model)\n";   ; muestra contraejemplo si SAT
        // out << "\n";
    }

    // ------------------------------------------------------------------ //
    //  Exporta TODAS las VCs de un método en un único fichero .smt2
    // ------------------------------------------------------------------ //
    void exportAll(const std::vector<VC>& vcs, const TablaSimbolos* ts) {
        // TODO VER-8:
        // out << "(set-logic QF_LIA)\n";  ; Quantifier-Free Linear Integer Arithmetic
        // for (const auto& vc : vcs) {
        //     out << "(push 1)\n";         ; aísla cada VC en su propio contexto
        //     exportVC(vc, ts);
        //     out << "(pop 1)\n\n";
        // }
        // out << "(exit)\n";
    }

    // ------------------------------------------------------------------ //
    //  [VER-10] Interpreta la salida de Z3 y reporta el resultado
    //
    //  UNSAT → VC válida (programa correcto en este punto)
    //  SAT   → bug encontrado, muestra el contraejemplo
    // ------------------------------------------------------------------ //
    static void parseZ3Output(const std::string& output,
                               const std::string& vcDescription) {
        // TODO VER-10:
        // if (output.find("unsat") != std::string::npos) {
        //     std::cout << "✓  " << vcDescription << "\n";
        // } else if (output.find("sat") != std::string::npos) {
        //     std::cerr << "✗  " << vcDescription << " — CONTRAEJEMPLO ENCONTRADO\n";
        //     std::cerr << output << "\n";
        // } else {
        //     std::cerr << "?  " << vcDescription << " — RESULTADO DESCONOCIDO\n";
        // }
    }
};

#endif
