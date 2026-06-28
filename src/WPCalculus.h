#ifndef _WP_CALCULUS_H
#define _WP_CALCULUS_H

// [VER-4] WP(x := e, Q)     = Q[e/x]
// [VER-5] WP(S1;S2, Q)      = WP(S1, WP(S2, Q))
// [VER-6] WP(while I {S}, Q) = I  (las VCs de bucle las genera VCGenerator)
//
// Implementación con continuaciones para manejar retornos anticipados.
// Un `return e` dentro de un if-sin-else provoca que la regla de
// composición naive sea incorrecta; aquí procesamos el bloque forward
// pasando la "cola" de sentencias como continuación explícita.
//
// Dijkstra, "A Discipline of Programming" (1976)
// Hoare, "An Axiomatic Basis for Computer Programming" (1969)

#include "ASTNodes.h"
#include "Predicate.h"
#include <vector>
#include <iostream>

class WPCalculus {
public:

    // Punto de entrada público
    static Predicate* wp(const StmtNode* stmt, const Predicate* Q) {
        if (!stmt) return Q->clone();
        std::vector<const StmtNode*> seq = { stmt };
        return wpSeq(seq, 0, Q);
    }

    static Predicate* wp(const BlockNode* block, const Predicate* Q) {
        std::vector<const StmtNode*> seq;
        for (const auto& s : block->statements)
            seq.push_back(s.get());
        return wpSeq(seq, 0, Q);
    }

    // Wrapper público para que VCGenerator pueda llamar a wpSeq directamente
    static Predicate* wpSeqPub(const std::vector<const StmtNode*>& stmts, const Predicate* Q) {
        return wpSeq(stmts, 0, Q);
    }

    // [VER-4]  WP(x := e, Q) = Q[e/x]
    static Predicate* wpAssign(const AssignNode* node, const Predicate* Q) {
        if (dynamic_cast<const ReadNode*>(node->value.get()))
            return Q->clone();  // entrada nondeterminista
        Predicate* exprPred = fromExpr(node->value.get());
        Predicate* result   = Q->subst(node->target->name, exprPred);
        delete exprPred;
        return result;
    }

    // [VER-6] WP del bucle = invariante (si existe)
    static Predicate* wpWhile(const WhileNode* node, const Predicate* Q) {
        if (!node->invariant) {
            std::cerr << "Warning: bucle sin @invariant — verificacion incompleta\n";
            return Q->clone();
        }
        return fromExpr(node->invariant.get());
    }

    static Predicate* wpReturn(const ReturnNode* node, const Predicate* Q) {
        if (!node->expr) return Q->clone();
        Predicate* exprPred = fromExpr(node->expr.get());
        Predicate* result   = Q->subst("result", exprPred);
        delete exprPred;
        return result;
    }

private:
    // ------------------------------------------------------------------ //
    //  wpSeq: WP de una secuencia de sentencias con continuación explícita.
    //
    //  Procesa HACIA DELANTE (no en reversa) para manejar retornos
    //  anticipados correctamente:
    //
    //  WP(return e; resto, Q)         = Q[e/result]   ← ignora `resto`
    //  WP(x:=e; resto, Q)             = WP(resto,Q)[e/x]
    //  WP(if(B) S1 else S2; resto, Q) = (B ==> WP(S1++resto, Q))
    //                                 && (!B ==> WP(S2++resto, Q))
    // ------------------------------------------------------------------ //
    static Predicate* wpSeq(const std::vector<const StmtNode*>& stmts,
                             int idx,
                             const Predicate* Q) {
        // Avanza sobre nulls y definiciones de método
        while (idx < (int)stmts.size() &&
               (!stmts[idx] || dynamic_cast<const MethodNode*>(stmts[idx])))
            idx++;

        if (idx >= (int)stmts.size()) return Q->clone();  // fin del bloque

        const StmtNode* s = stmts[idx];

        // ── Return: termina el camino, usa Q directamente ──────────────
        if (auto* r = dynamic_cast<const ReturnNode*>(s))
            return wpReturn(r, Q);

        // ── Asignación: WP(x:=e; resto, Q) = WP(resto,Q)[e/x] ────────
        if (auto* a = dynamic_cast<const AssignNode*>(s)) {
            Predicate* restWP = wpSeq(stmts, idx + 1, Q);
            Predicate* result = wpAssign(a, restWP);
            delete restWP;
            return result;
        }

        // ── Bloque anidado: inlining en la secuencia ───────────────────
        if (auto* b = dynamic_cast<const BlockNode*>(s)) {
            std::vector<const StmtNode*> flat;
            for (const auto& ss : b->statements) flat.push_back(ss.get());
            for (int i = idx + 1; i < (int)stmts.size(); i++) flat.push_back(stmts[i]);
            return wpSeq(flat, 0, Q);
        }

        // ── If/Else: bifurca la continuación para cada rama ────────────
        if (auto* i = dynamic_cast<const IfNode*>(s)) {
            Predicate* B = fromExpr(i->condition.get());

            // Continuación (sentencias que siguen al if)
            std::vector<const StmtNode*> cont(stmts.begin() + idx + 1, stmts.end());

            Predicate* wp1 = wpBranchAndCont(i->thenPart.get(), cont, Q);
            Predicate* wp2 = wpBranchAndCont(i->elsePart.get(), cont, Q);

            return new AndPred(
                new ImpliesPred(B->clone(), wp1),
                new ImpliesPred(new NotPred(B), wp2)
            );
        }

        // ── While: WP del bucle (las VCs de invariante van aparte) ─────
        if (auto* w = dynamic_cast<const WhileNode*>(s)) {
            Predicate* restWP = wpSeq(stmts, idx + 1, Q);
            Predicate* result = wpWhile(w, restWP);
            delete restWP;
            return result;
        }

        // ── Otras sentencias (print, etc.): sin efecto lógico ──────────
        return wpSeq(stmts, idx + 1, Q);
    }

    // WP de una rama (posiblemente nula) seguida de la continuación `cont`
    static Predicate* wpBranchAndCont(const StmtNode* branch,
                                       const std::vector<const StmtNode*>& cont,
                                       const Predicate* Q) {
        std::vector<const StmtNode*> seq;
        if (branch) {
            if (auto* b = dynamic_cast<const BlockNode*>(branch))
                for (const auto& ss : b->statements) seq.push_back(ss.get());
            else
                seq.push_back(branch);
        }
        for (const auto* s : cont) seq.push_back(s);
        return wpSeq(seq, 0, Q);
    }
};

#endif
