#ifndef _VC_GENERATOR_H
#define _VC_GENERATOR_H

// [VER-7] Generación de Verification Conditions (VCs)
//
// Una VC es una fórmula lógica que debe ser VÁLIDA para que el programa
// sea correcto. Se verifica enviándola a Z3 (ver SMTExporter.h).
//
// Para un método { @pre P } body { @post Q }:
//   VC principal:  P  ==>  WP(body, Q)
//
// Para un bucle { @invariant I } while (B) { S }:
//   VC1 (initiation):    pre  ==>  I
//   VC2 (preservation):  (I && B)  ==>  WP(S, I)
//   VC3 (use):           (I && !B) ==>  Q

#include "ASTNodes.h"
#include "Predicate.h"
#include "WPCalculus.h"
#include <vector>
#include <string>
#include <memory>

// Una Verification Condition: descripción + fórmula lógica
struct VC {
    std::string description;           // texto explicativo para el usuario
    std::unique_ptr<Predicate> formula; // la fórmula que debe ser válida

    VC(const std::string& desc, Predicate* f)
        : description(desc), formula(f) {}
};

class VCGenerator {
public:

    // ------------------------------------------------------------------ //
    //  Genera todas las VCs para un método anotado.
    //  Retorna lista vacía si el método no tiene @pre/@post.
    // ------------------------------------------------------------------ //
    static std::vector<VC> generate(const MethodNode* method) {
        std::vector<VC> vcs;

        if (!method->postcondition) return vcs;

        // TODO VER-7:
        // 1. Obtén la postcondición Q = fromExpr(method->postcondition.get())
        // 2. Calcula WP = WPCalculus::wp(method->body.get(), Q)
        // 3. Obtén la precondición P:
        //      - Si hay @pre: P = fromExpr(method->precondition.get())
        //      - Si no hay:   P = TruePred()
        // 4. VC principal: P ==> WP
        //    vcs.push_back(VC("VC: " + method->name + " correctness",
        //                     new ImpliesPred(P, WP)));
        //
        // Para cada WhileNode en el cuerpo, genera VCs adicionales:
        //   (ver collectWhileVCs)

        return vcs;
    }

    // ------------------------------------------------------------------ //
    //  Recorre el cuerpo de un método buscando bucles con @invariant
    //  y genera sus VCs (initiation, preservation, use).
    // ------------------------------------------------------------------ //
    static void collectWhileVCs(const BlockNode* block,
                                 const Predicate* contextPre,
                                 const Predicate* Q,
                                 std::vector<VC>& vcs) {
        // TODO VER-6 + VER-7:
        // Para cada stmt en block->statements:
        //   Si es WhileNode w con w->invariant != nullptr:
        //     I = fromExpr(w->invariant.get())
        //     B = fromExpr(w->condition.get())
        //
        //     VC1: contextPre ==> I    (el invariante vale al entrar)
        //     VC2: And(I, B)  ==> WP(w->body, I)   (el cuerpo preserva I)
        //     VC3: And(I, Not(B)) ==> Q              (I && !B implica post)
    }

    // ------------------------------------------------------------------ //
    //  Imprime las VCs en formato legible (para debug)
    // ------------------------------------------------------------------ //
    static void dump(const std::vector<VC>& vcs, std::ostream& out = std::cerr) {
        out << "=== Verification Conditions ===\n";
        for (int i = 0; i < (int)vcs.size(); ++i) {
            out << "VC" << i << ": " << vcs[i].description << "\n";
            out << "     " << (vcs[i].formula ? vcs[i].formula->toString() : "?") << "\n";
        }
        out << "================================\n";
    }
};

#endif
