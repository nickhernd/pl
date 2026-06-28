#ifndef _VC_GENERATOR_H
#define _VC_GENERATOR_H

// [VER-6]  Invariantes de bucle: VC1 iniciación, VC2 preservación, VC3 uso
// [VER-7]  VC principal: P ==> WP(body, Q)
// [VER-9]  Seguridad en memoria: sin división por cero
// [VER-11] Terminación: variante >= 0 mientras el bucle está activo

#include "ASTNodes.h"
#include "Predicate.h"
#include "WPCalculus.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>

struct VC {
    std::string description;
    std::unique_ptr<Predicate> formula;
    const TablaSimbolos* methodTS;  // tabla local del método (para declarar vars en SMT2)

    VC(const std::string& desc, Predicate* f, const TablaSimbolos* ts = nullptr)
        : description(desc), formula(f), methodTS(ts) {}
};

class VCGenerator {
public:

    // ------------------------------------------------------------------ //
    //  [VER-7] VC principal de corrección + VCs de bucles
    //  { @pre P } body { @post Q }  →  VC: P ==> WP(body, Q)
    // ------------------------------------------------------------------ //
    static std::vector<VC> generate(const MethodNode* method) {
        std::vector<VC> vcs;
        if (!method->postcondition || !method->body) return vcs;

        const TablaSimbolos* ts = method->body->symbols;

        Predicate* Q  = fromExpr(method->postcondition.get());
        Predicate* WP = WPCalculus::wp(method->body.get(), Q);
        Predicate* P  = method->precondition
            ? fromExpr(method->precondition.get())
            : new TruePred();

        vcs.push_back(VC("[" + method->name + "] correctitud",
                         new ImpliesPred(P->clone(), WP), ts));

        // VCs adicionales para bucles con @invariant
        collectWhileVCsFromBlock(method->body.get(), P, Q, method->name, ts, vcs);
        delete P;
        delete Q;

        return vcs;
    }

    // ------------------------------------------------------------------ //
    //  [VER-9] Seguridad en memoria: denominador != 0 para / y %
    // ------------------------------------------------------------------ //
    static std::vector<VC> generateSafety(const MethodNode* method) {
        std::vector<VC> vcs;
        if (!method->body) return vcs;
        const TablaSimbolos* ts = method->body->symbols;
        Predicate* pre = method->precondition
            ? fromExpr(method->precondition.get())
            : new TruePred();
        scanDivByZeroStmt(method->body.get(), pre, method->name, ts, vcs);
        delete pre;
        return vcs;
    }

    // ------------------------------------------------------------------ //
    //  [VER-11] Terminación: para bucles con @variant V
    //  VC: (I && B) ==> V >= 0
    // ------------------------------------------------------------------ //
    static std::vector<VC> generateTermination(const MethodNode* method) {
        std::vector<VC> vcs;
        if (!method->body) return vcs;
        const TablaSimbolos* ts = method->body->symbols;
        scanTerminationStmt(method->body.get(), method->name, ts, vcs);
        return vcs;
    }

    // ------------------------------------------------------------------ //
    //  Debug: muestra las VCs en formato legible
    // ------------------------------------------------------------------ //
    static void dump(const std::vector<VC>& vcs, std::ostream& out = std::cerr) {
        out << "=== Verification Conditions ===\n";
        for (int i = 0; i < (int)vcs.size(); ++i) {
            out << "VC" << i << ": " << vcs[i].description << "\n";
            out << "     " << (vcs[i].formula ? vcs[i].formula->toString() : "?") << "\n";
        }
        out << "================================\n";
    }

private:

    // ------------------------------------------------------------------ //
    //  [VER-6] Escaneo secuencial del bloque para generar VCs de bucle
    //
    //  Procesa sentencias hacia delante. Para cada while con @invariant:
    //  - VC1: P ==> WP(stmts_antes, I)   (iniciación con contexto correcto)
    //  - VC2: (I && B) ==> WP(body, I)   (preservación)
    //  - VC3: (I && !B) ==> WP(stmts_después, Q)  (uso con continuación)
    // ------------------------------------------------------------------ //
    static void collectWhileVCsFromBlock(const BlockNode* block,
                                          const Predicate* P,
                                          const Predicate* Q,
                                          const std::string& ctx,
                                          const TablaSimbolos* ts,
                                          std::vector<VC>& vcs) {
        if (!block) return;
        const auto& stmts = block->statements;

        for (int idx = 0; idx < (int)stmts.size(); idx++) {
            const StmtNode* s = stmts[idx].get();
            if (!s) continue;

            if (auto* w = dynamic_cast<const WhileNode*>(s)) {
                if (w->invariant) {
                    Predicate* I = fromExpr(w->invariant.get());
                    Predicate* B = fromExpr(w->condition.get());

                    // VC1: P ==> WP([stmts_antes_del_while], I)
                    // Computa WP de lo que viene antes del while con I como postcondición
                    std::vector<const StmtNode*> before;
                    for (int j = 0; j < idx; j++) before.push_back(stmts[j].get());
                    Predicate* initContext = WPCalculus::wpSeqPub(before, I);
                    vcs.push_back(VC("[" + ctx + "] invariant iniciacion",
                        new ImpliesPred(P->clone(), initContext), ts));

                    // VC2: (I && B) ==> WP(body, I)
                    Predicate* IandB  = new AndPred(I->clone(), B->clone());
                    Predicate* bodyWP = WPCalculus::wp(w->body.get(), I);
                    vcs.push_back(VC("[" + ctx + "] invariant preservacion",
                        new ImpliesPred(IandB, bodyWP), ts));

                    // VC3: (I && !B) ==> WP([stmts_después_del_while], Q)
                    std::vector<const StmtNode*> after;
                    for (int j = idx+1; j < (int)stmts.size(); j++)
                        after.push_back(stmts[j].get());
                    Predicate* usePost = WPCalculus::wpSeqPub(after, Q);
                    Predicate* IandNotB = new AndPred(I, new NotPred(B));
                    vcs.push_back(VC("[" + ctx + "] invariant uso",
                        new ImpliesPred(IandNotB, usePost), ts));

                    // Recursa en el cuerpo del bucle
                    if (auto* b = dynamic_cast<const BlockNode*>(w->body.get()))
                        collectWhileVCsFromBlock(b, new AndPred(I->clone(), B->clone()), Q, ctx, ts, vcs);
                } else {
                    // Sin @invariant: recursa de todas formas
                    if (auto* b = dynamic_cast<const BlockNode*>(w->body.get()))
                        collectWhileVCsFromBlock(b, P, Q, ctx, ts, vcs);
                }

            } else if (auto* i = dynamic_cast<const IfNode*>(s)) {
                if (i->thenPart)
                    if (auto* b = dynamic_cast<const BlockNode*>(i->thenPart.get()))
                        collectWhileVCsFromBlock(b, P, Q, ctx, ts, vcs);
                if (i->elsePart)
                    if (auto* b = dynamic_cast<const BlockNode*>(i->elsePart.get()))
                        collectWhileVCsFromBlock(b, P, Q, ctx, ts, vcs);
            }
        }
    }

    // ── División por cero ────────────────────────────────────────────────

    static void scanDivByZeroExpr(const ExprNode* expr,
                                   const Predicate* pre,
                                   const std::string& ctx,
                                   const TablaSimbolos* ts,
                                   std::vector<VC>& vcs) {
        if (!expr) return;
        if (auto* bin = dynamic_cast<const BinaryExprNode*>(expr)) {
            if (bin->op == "/" || bin->op == "%") {
                Predicate* divisor = fromExpr(bin->right.get());
                Predicate* notZero = new BinaryPred("!=", divisor, new IntLitPred(0));
                vcs.push_back(VC("[" + ctx + "] division por cero (" + bin->op + ")",
                                 new ImpliesPred(pre->clone(), notZero), ts));
            }
            scanDivByZeroExpr(bin->left.get(),  pre, ctx, ts, vcs);
            scanDivByZeroExpr(bin->right.get(), pre, ctx, ts, vcs);
        }
        if (auto* u = dynamic_cast<const UnaryExprNode*>(expr))
            scanDivByZeroExpr(u->expr.get(), pre, ctx, ts, vcs);
    }

    static void scanDivByZeroStmt(const StmtNode* stmt,
                                   const Predicate* pre,
                                   const std::string& ctx,
                                   const TablaSimbolos* ts,
                                   std::vector<VC>& vcs) {
        if (!stmt) return;
        if (auto* b = dynamic_cast<const BlockNode*>(stmt)) {
            for (const auto& s : b->statements)
                scanDivByZeroStmt(s.get(), pre, ctx, ts, vcs);
        } else if (auto* a = dynamic_cast<const AssignNode*>(stmt)) {
            scanDivByZeroExpr(a->value.get(), pre, ctx, ts, vcs);
        } else if (auto* p = dynamic_cast<const PrintNode*>(stmt)) {
            scanDivByZeroExpr(p->expr.get(), pre, ctx, ts, vcs);
        } else if (auto* r = dynamic_cast<const ReturnNode*>(stmt)) {
            if (r->expr) scanDivByZeroExpr(r->expr.get(), pre, ctx, ts, vcs);
        } else if (auto* i = dynamic_cast<const IfNode*>(stmt)) {
            scanDivByZeroExpr(i->condition.get(), pre, ctx, ts, vcs);
            scanDivByZeroStmt(i->thenPart.get(), pre, ctx, ts, vcs);
            scanDivByZeroStmt(i->elsePart.get(), pre, ctx, ts, vcs);
        } else if (auto* w = dynamic_cast<const WhileNode*>(stmt)) {
            scanDivByZeroExpr(w->condition.get(), pre, ctx, ts, vcs);
            scanDivByZeroStmt(w->body.get(), pre, ctx, ts, vcs);
        }
    }

    // ── Terminación ──────────────────────────────────────────────────────

    static void scanTerminationStmt(const StmtNode* stmt,
                                     const std::string& ctx,
                                     const TablaSimbolos* ts,
                                     std::vector<VC>& vcs) {
        if (!stmt) return;
        if (auto* b = dynamic_cast<const BlockNode*>(stmt)) {
            for (const auto& s : b->statements)
                scanTerminationStmt(s.get(), ctx, ts, vcs);
        } else if (auto* w = dynamic_cast<const WhileNode*>(stmt)) {
            if (w->variant) {
                Predicate* V    = fromExpr(w->variant.get());
                Predicate* B    = fromExpr(w->condition.get());
                Predicate* I    = w->invariant
                    ? fromExpr(w->invariant.get())
                    : (Predicate*)new TruePred();
                Predicate* ante = new AndPred(I, B);
                Predicate* cons = new BinaryPred(">=", V, new IntLitPred(0));
                vcs.push_back(VC("[" + ctx + "] terminacion (variante >= 0)",
                    new ImpliesPred(ante, cons), ts));
            }
            scanTerminationStmt(w->body.get(), ctx, ts, vcs);
        } else if (auto* i = dynamic_cast<const IfNode*>(stmt)) {
            scanTerminationStmt(i->thenPart.get(), ctx, ts, vcs);
            scanTerminationStmt(i->elsePart.get(), ctx, ts, vcs);
        }
    }
};

#endif
