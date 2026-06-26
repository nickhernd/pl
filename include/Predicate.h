#ifndef _PREDICATE_H
#define _PREDICATE_H

// [VER-2] Representación de Predicados Lógicos (Fórmulas de Primer Orden)
//
// Esta jerarquía es la base de todo el cálculo WP (VER-4 a VER-7).
// Operaciones clave que el usuario implementará:
//   - subst(var, expr): sustitución textual P[expr/var]  — necesaria para la
//                       regla de la asignación (VER-4): WP(x:=e, Q) = Q[e/x]
//   - toSMT():          conversión a SMT-Lib2 para Z3 (VER-8)
//   - toString():       representación legible para debug

#include <string>
#include <memory>
#include <sstream>

// Forward declarations
class ExprNode;

// ===================================================================== //
//  Clase base abstracta
// ===================================================================== //

class Predicate {
public:
    virtual ~Predicate() {}

    // Sustitución textual: devuelve P con cada ocurrencia libre de 'var'
    // reemplazada por 'expr'. Fundamental para la regla de la asignación.
    // TODO VER-4: usarás esto en WPCalculus::wpAssign
    virtual Predicate* subst(const std::string& var,
                             const Predicate* expr) const = 0;

    // Conversión a SMT-Lib2 (notación prefija tipo Lisp)
    // TODO VER-8: usarás esto en SMTExporter
    virtual std::string toSMT() const = 0;

    // Representación legible para depuración
    virtual std::string toString() const = 0;

    // Copia profunda del predicado
    virtual Predicate* clone() const = 0;
};

// ===================================================================== //
//  Predicados atómicos
// ===================================================================== //

// true
class TruePred : public Predicate {
public:
    Predicate* subst(const std::string&, const Predicate*) const override {
        return new TruePred();
    }
    std::string toSMT()    const override { return "true"; }
    std::string toString() const override { return "true"; }
    Predicate*  clone()    const override { return new TruePred(); }
};

// false
class FalsePred : public Predicate {
public:
    Predicate* subst(const std::string&, const Predicate*) const override {
        return new FalsePred();
    }
    std::string toSMT()    const override { return "false"; }
    std::string toString() const override { return "false"; }
    Predicate*  clone()    const override { return new FalsePred(); }
};

// Referencia a variable: x, y, sum, ...
class VarPred : public Predicate {
public:
    std::string name;
    explicit VarPred(const std::string& n) : name(n) {}

    // Sustitución: si soy la variable sustituida, me reemplazo por expr
    Predicate* subst(const std::string& var, const Predicate* expr) const override {
        if (name == var) return expr->clone();
        return new VarPred(name);
    }
    std::string toSMT()    const override { return name; }
    std::string toString() const override { return name; }
    Predicate*  clone()    const override { return new VarPred(name); }
};

// \result — valor de retorno de la función (usado en @post)
class ResultPred : public Predicate {
public:
    Predicate* subst(const std::string& var, const Predicate* expr) const override {
        if (var == "result") return expr->clone();
        return new ResultPred();
    }
    std::string toSMT()    const override { return "result"; }
    std::string toString() const override { return "result"; }
    Predicate*  clone()    const override { return new ResultPred(); }
};

// Constante entera: 0, 1, 42, ...
class IntLitPred : public Predicate {
public:
    long value;
    explicit IntLitPred(long v) : value(v) {}

    Predicate* subst(const std::string&, const Predicate*) const override {
        return new IntLitPred(value);
    }
    std::string toSMT() const override {
        if (value < 0) return "(- " + std::to_string(-value) + ")";
        return std::to_string(value);
    }
    std::string toString() const override { return std::to_string(value); }
    Predicate*  clone()    const override { return new IntLitPred(value); }
};

// Constante real: 3.14, 0.5, ...
class RealLitPred : public Predicate {
public:
    double value;
    explicit RealLitPred(double v) : value(v) {}

    Predicate* subst(const std::string&, const Predicate*) const override {
        return new RealLitPred(value);
    }
    std::string toSMT() const override {
        std::ostringstream os;
        os << value;
        std::string s = os.str();
        if (s.find('.') == std::string::npos) s += ".0";
        if (value < 0) return "(- " + s.substr(1) + ")";
        return s;
    }
    std::string toString() const override { std::ostringstream os; os << value; return os.str(); }
    Predicate*  clone()    const override { return new RealLitPred(value); }
};

// ===================================================================== //
//  Predicados binarios (aritmética y comparación)
// ===================================================================== //

// op: +, -, *, / (aritmética) | ==, !=, <, <=, >, >= (comparación)
class BinaryPred : public Predicate {
public:
    std::string op;
    std::unique_ptr<Predicate> left, right;

    BinaryPred(const std::string& o, Predicate* l, Predicate* r)
        : op(o), left(l), right(r) {}

    Predicate* subst(const std::string& var, const Predicate* expr) const override {
        return new BinaryPred(op,
                              left->subst(var, expr),
                              right->subst(var, expr));
    }

    std::string toSMT() const override {
        // SMT-Lib2 usa prefijo y operadores distintos para algunos casos
        std::string smtOp = op;
        if (op == "!=") smtOp = "distinct";
        if (op == "&&") smtOp = "and";
        if (op == "||") smtOp = "or";
        return "(" + smtOp + " " + left->toSMT() + " " + right->toSMT() + ")";
    }

    std::string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }

    Predicate* clone() const override {
        return new BinaryPred(op, left->clone(), right->clone());
    }
};

// ===================================================================== //
//  Conectivos lógicos
// ===================================================================== //

class AndPred : public Predicate {
public:
    std::unique_ptr<Predicate> left, right;
    AndPred(Predicate* l, Predicate* r) : left(l), right(r) {}

    Predicate* subst(const std::string& v, const Predicate* e) const override {
        return new AndPred(left->subst(v, e), right->subst(v, e));
    }
    std::string toSMT()    const override { return "(and " + left->toSMT()    + " " + right->toSMT()    + ")"; }
    std::string toString() const override { return "("     + left->toString() + " && " + right->toString() + ")"; }
    Predicate*  clone()    const override { return new AndPred(left->clone(), right->clone()); }
};

class OrPred : public Predicate {
public:
    std::unique_ptr<Predicate> left, right;
    OrPred(Predicate* l, Predicate* r) : left(l), right(r) {}

    Predicate* subst(const std::string& v, const Predicate* e) const override {
        return new OrPred(left->subst(v, e), right->subst(v, e));
    }
    std::string toSMT()    const override { return "(or "  + left->toSMT()    + " " + right->toSMT()    + ")"; }
    std::string toString() const override { return "("     + left->toString() + " || " + right->toString() + ")"; }
    Predicate*  clone()    const override { return new OrPred(left->clone(), right->clone()); }
};

class NotPred : public Predicate {
public:
    std::unique_ptr<Predicate> pred;
    explicit NotPred(Predicate* p) : pred(p) {}

    Predicate* subst(const std::string& v, const Predicate* e) const override {
        return new NotPred(pred->subst(v, e));
    }
    std::string toSMT()    const override { return "(not " + pred->toSMT()    + ")"; }
    std::string toString() const override { return "(!"    + pred->toString() + ")"; }
    Predicate*  clone()    const override { return new NotPred(pred->clone()); }
};

// P ==> Q  (equivalente a !P || Q, pero más legible)
class ImpliesPred : public Predicate {
public:
    std::unique_ptr<Predicate> ante, cons;  // antecedente, consecuente
    ImpliesPred(Predicate* a, Predicate* c) : ante(a), cons(c) {}

    Predicate* subst(const std::string& v, const Predicate* e) const override {
        return new ImpliesPred(ante->subst(v, e), cons->subst(v, e));
    }
    std::string toSMT()    const override { return "(=> "   + ante->toSMT()    + " " + cons->toSMT()    + ")"; }
    std::string toString() const override { return "("      + ante->toString() + " ==> " + cons->toString() + ")"; }
    Predicate*  clone()    const override { return new ImpliesPred(ante->clone(), cons->clone()); }
};

// ===================================================================== //
//  Negación aritmética  (-x)
// ===================================================================== //

class NegPred : public Predicate {
public:
    std::unique_ptr<Predicate> pred;
    explicit NegPred(Predicate* p) : pred(p) {}

    Predicate* subst(const std::string& v, const Predicate* e) const override {
        return new NegPred(pred->subst(v, e));
    }
    std::string toSMT()    const override { return "(- "  + pred->toSMT()    + ")"; }
    std::string toString() const override { return "(-"   + pred->toString() + ")"; }
    Predicate*  clone()    const override { return new NegPred(pred->clone()); }
};

// ===================================================================== //
//  Fábrica: convierte un ExprNode del AST a un Predicate
//  (declarada aquí, definida en Predicate.cc o en el .h si es inline)
// ===================================================================== //

// Incluido aquí para no necesitar un .cc separado
// El include de ASTNodes debe hacerse ANTES de incluir Predicate.h si se
// quiere usar fromExpr. En WPCalculus.h se incluye después de ASTNodes.h.
#ifdef _AST_NODES_H
#include "TablaSimbolos.h"

// Convierte un nodo ExprNode del AST a la jerarquía Predicate.
// Útil para transformar las anotaciones @pre/@post/@invariant.
inline Predicate* fromExpr(const ExprNode* e) {
    if (!e) return new TruePred();

    if (auto* n = dynamic_cast<const IntLiteralNode*>(e))
        return new IntLitPred(n->value);

    if (auto* n = dynamic_cast<const FloatLiteralNode*>(e))
        return new RealLitPred(n->value);

    if (auto* n = dynamic_cast<const BoolLiteralNode*>(e))
        return n->value ? (Predicate*)new TruePred() : new FalsePred();

    if (dynamic_cast<const ResultNode*>(e))
        return new ResultPred();

    if (auto* n = dynamic_cast<const IdentifierNode*>(e))
        return new VarPred(n->name);

    if (auto* n = dynamic_cast<const BinaryExprNode*>(e)) {
        Predicate* l = fromExpr(n->left.get());
        Predicate* r = fromExpr(n->right.get());
        const std::string& op = n->op;
        if (op == "&&") return new AndPred(l, r);
        if (op == "||") return new OrPred(l, r);
        if (op == "==>") return new ImpliesPred(l, r);
        return new BinaryPred(op, l, r);
    }

    if (auto* n = dynamic_cast<const UnaryExprNode*>(e)) {
        Predicate* p = fromExpr(n->expr.get());
        if (n->op == "!") return new NotPred(p);
        if (n->op == "-") return new NegPred(p);
        return p;
    }

    // Fallback: no reconocido
    return new TruePred();
}
#endif  // _AST_NODES_H

#endif  // _PREDICATE_H
