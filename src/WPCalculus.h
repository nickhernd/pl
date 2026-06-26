#ifndef _WP_CALCULUS_H
#define _WP_CALCULUS_H

// [VER-4] Regla de la Asignación:    WP(x := e, Q)  =  Q[e/x]
// [VER-5] Regla de la Composición:   WP(S1;S2, Q)   =  WP(S1, WP(S2, Q))
// [VER-6] Regla del Bucle:           requiere @invariant I
//
// Referencia: Dijkstra, "A Discipline of Programming" (1976)
//             Hoare, "An Axiomatic Basis for Computer Programming" (1969)
//
// Uso:
//   Predicate* post = fromExpr(method->postcondition.get());
//   Predicate* wp   = WPCalculus::wp(method->body.get(), post);
//   // wp es la precondición más débil del método
//   // La VC es: pre => wp

#include "ASTNodes.h"
#include "Predicate.h"

class WPCalculus {
public:

    // ------------------------------------------------------------------ //
    //  Punto de entrada: WP(stmt, Q)
    //  Calcula la precondición más débil de una sentencia dado Q.
    // ------------------------------------------------------------------ //
    static Predicate* wp(const StmtNode* stmt, const Predicate* Q) {
        if (!stmt) return Q->clone();

        // TODO: hacer dispatch por tipo de nodo usando dynamic_cast
        // Ejemplo:
        //   if (auto* a = dynamic_cast<const AssignNode*>(stmt))
        //       return wpAssign(a, Q);
        //   if (auto* b = dynamic_cast<const BlockNode*>(stmt))
        //       return wpBlock(b, Q);
        //   if (auto* i = dynamic_cast<const IfNode*>(stmt))
        //       return wpIf(i, Q);
        //   if (auto* w = dynamic_cast<const WhileNode*>(stmt))
        //       return wpWhile(w, Q);
        //   if (auto* r = dynamic_cast<const ReturnNode*>(stmt))
        //       return wpReturn(r, Q);

        return Q->clone();  // eliminar cuando implementes el dispatch
    }

    // ------------------------------------------------------------------ //
    //  [VER-4] Regla de la Asignación
    //
    //  { Q[e/x] }  x := e  { Q }
    //
    //  WP(x := e, Q) = Q con cada aparición libre de x sustituida por e
    // ------------------------------------------------------------------ //
    static Predicate* wpAssign(const AssignNode* node, const Predicate* Q) {
        // TODO VER-4:
        // 1. Convierte node->value (ExprNode*) a Predicate* usando fromExpr()
        // 2. Usa Q->subst(node->target->name, exprPred) para realizar la sustitución
        // 3. Devuelve el resultado
        //
        // Ejemplo: WP(x := x+1, x > 5)
        //   exprPred = BinaryPred("+", VarPred("x"), IntLitPred(1))
        //   resultado = BinaryPred(">", BinaryPred("+", VarPred("x"), IntLitPred(1)), IntLitPred(5))
        //             = (x+1) > 5
        return Q->clone();  // reemplazar con la implementación real
    }

    // ------------------------------------------------------------------ //
    //  [VER-5] Regla de la Composición (Secuencia)
    //
    //  { P }  S1; S2  { Q }
    //  si  { P }  S1  { R }  y  { R }  S2  { Q }
    //
    //  WP(S1; S2, Q) = WP(S1, WP(S2, Q))
    //  → procesar las sentencias en orden INVERSO
    // ------------------------------------------------------------------ //
    static Predicate* wpBlock(const BlockNode* block, const Predicate* Q) {
        // TODO VER-5:
        // Itera sobre block->statements en orden INVERSO.
        // Empieza con Q y aplica wp() en cada paso:
        //   current = Q
        //   for stmt in reverse(statements):
        //       current = wp(stmt, current)
        // Devuelve current
        return Q->clone();  // reemplazar con la implementación real
    }

    // ------------------------------------------------------------------ //
    //  Regla del Condicional
    //
    //  { P }  if B then S1 else S2  { Q }
    //  si { P && B } S1 { Q }  y  { P && !B } S2 { Q }
    //
    //  WP(if B then S1 else S2, Q) =
    //      (B ==> WP(S1, Q))  &&  (!B ==> WP(S2, Q))
    // ------------------------------------------------------------------ //
    static Predicate* wpIf(const IfNode* node, const Predicate* Q) {
        // TODO:
        // 1. Convierte node->condition a Predicate* usando fromExpr()
        // 2. Calcula wp1 = wp(node->thenPart, Q)
        // 3. Calcula wp2 = wp(node->elsePart, Q)  [o TruePred() si no hay else]
        // 4. Devuelve  And(Implies(B, wp1), Implies(Not(B), wp2))
        return Q->clone();  // reemplazar con la implementación real
    }

    // ------------------------------------------------------------------ //
    //  [VER-6] Regla del Bucle con Invariante
    //
    //  Para verificar  while (B) @invariant I { S }  con postcondición Q:
    //
    //  Se generan tres Verification Conditions (no un solo WP):
    //    VC1 (initiation):    pre  ==>  I
    //    VC2 (preservation):  (I && B)  ==>  WP(S, I)
    //    VC3 (termination):   (I && !B) ==>  Q
    //
    //  WP del bucle = I  (asumiendo que I es correcta)
    //
    //  Nota: si no hay @invariant, la verificación no es posible.
    //        Reporta un error/advertencia.
    // ------------------------------------------------------------------ //
    static Predicate* wpWhile(const WhileNode* node, const Predicate* Q) {
        // TODO VER-6:
        // Si node->invariant == nullptr: devuelve Q->clone() con advertencia
        // Si tiene invariante I:
        //   WP del bucle = fromExpr(node->invariant.get())
        //   Las VCs se generan en VCGenerator, no aquí
        return Q->clone();  // reemplazar con la implementación real
    }

    // ------------------------------------------------------------------ //
    //  Regla del Return
    //
    //  WP(return e, Q) = Q[e/result]
    //  → sustituye "result" en Q por el valor de retorno
    // ------------------------------------------------------------------ //
    static Predicate* wpReturn(const ReturnNode* node, const Predicate* Q) {
        // TODO:
        // Si node->expr != nullptr:
        //   exprPred = fromExpr(node->expr.get())
        //   return Q->subst("result", exprPred)
        // Si void: return Q->clone()
        return Q->clone();  // reemplazar con la implementación real
    }
};

#endif
