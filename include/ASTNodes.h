#ifndef _AST_NODES_H
#define _AST_NODES_H

#include "Node.h"
#include <string>
#include <vector>

// Forward declarations are already in Visitor.h, which Node.h includes.

// [AST-3] Nodo para Literales (Int, Float)
class IntLiteralNode : public ExprNode {
public:
    int value;
    IntLiteralNode(int val, int l, int c) : ExprNode(l, c), value(val) {}
    void accept(Visitor* v) override { v->visit(this); }
};

class FloatLiteralNode : public ExprNode {
public:
    float value;
    FloatLiteralNode(float val, int l, int c) : ExprNode(l, c), value(val) {}
    void accept(Visitor* v) override { v->visit(this); }
};

class BoolLiteralNode : public ExprNode {
public:
    bool value;
    BoolLiteralNode(bool val, int l, int c) : ExprNode(l, c), value(val) {}
    void accept(Visitor* v) override { v->visit(this); }
};

// [AST-4] Nodo para Identificadores
class IdentifierNode : public ExprNode {
public:
    std::string name;
    IdentifierNode(const std::string& n, int l, int c) : ExprNode(l, c), name(n) {}
    void accept(Visitor* v) override { v->visit(this); }
};

// [AST-2] Nodo para Expresiones Binarias
class BinaryExprNode : public ExprNode {
public:
    std::string op;
    ExprNode* left;
    ExprNode* right;
    BinaryExprNode(const std::string& o, ExprNode* l_node, ExprNode* r_node, int l, int c) 
        : ExprNode(l, c), op(o), left(l_node), right(r_node) {}
    ~BinaryExprNode() {
        delete left;
        delete right;
    }
    void accept(Visitor* v) override { v->visit(this); }
};

class UnaryExprNode : public ExprNode {
public:
    std::string op;
    ExprNode* expr;
    UnaryExprNode(const std::string& o, ExprNode* e, int l, int c)
        : ExprNode(l, c), op(o), expr(e) {}
    ~UnaryExprNode() {
        delete expr;
    }
    void accept(Visitor* v) override { v->visit(this); }
};

// [AST-5] Estructura de Sentencias (StmtNode) & [AST-6] Nodo de Asignación
class AssignNode : public StmtNode {
public:
    IdentifierNode* target;
    ExprNode* value;
    AssignNode(IdentifierNode* t, ExprNode* v, int l, int c) 
        : StmtNode(l, c), target(t), value(v) {}
    ~AssignNode() {
        delete target;
        delete value;
    }
    void accept(Visitor* v) override { v->visit(this); }
};

// [AST-7] Nodo de Bloque (Listas de Stmts)
class BlockNode : public StmtNode {
public:
    std::vector<StmtNode*> statements;
    class TablaSimbolos* symbols;
    BlockNode(int l, int c) : StmtNode(l, c), symbols(nullptr) {}
    ~BlockNode() {
        for (auto s : statements) delete s;
    }
    void add(StmtNode* s) { if (s) statements.push_back(s); }
    void accept(Visitor* v) override { v->visit(this); }
};

// [AST-11] Soporte para If/Else en AST
class IfNode : public StmtNode {
public:
    ExprNode* condition;
    StmtNode* thenPart;
    StmtNode* elsePart;
    IfNode(ExprNode* cond, StmtNode* t, StmtNode* e, int l, int c)
        : StmtNode(l, c), condition(cond), thenPart(t), elsePart(e) {}
    ~IfNode() {
        delete condition;
        delete thenPart;
        if (elsePart) delete elsePart;
    }
    void accept(Visitor* v) override { v->visit(this); }
};

// [AST-12] Soporte para Bucles While en AST
class WhileNode : public StmtNode {
public:
    ExprNode* condition;
    StmtNode* body;
    WhileNode(ExprNode* cond, StmtNode* b, int l, int c)
        : StmtNode(l, c), condition(cond), body(b) {}
    ~WhileNode() {
        delete condition;
        delete body;
    }
    void accept(Visitor* v) override { v->visit(this); }
};

// Program Node
class ProgramNode : public Node {
public:
    BlockNode* root;
    ProgramNode(BlockNode* r) : Node(0, 0), root(r) {}
    ~ProgramNode() { delete root; }
    void accept(Visitor* v) override { v->visit(this); }
};

#endif
