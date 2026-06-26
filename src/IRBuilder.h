#ifndef _IR_BUILDER_H
#define _IR_BUILDER_H

// [IR-4] Traducción de Expresiones Aritméticas
// [IR-5] Traducción de Saltos Condicionales
// [IR-6] IR para Llamadas a Funciones
// Visitor que recorre el AST y emite cuádruplas IR

#include "ASTNodes.h"
#include "IR.h"
#include "TablaSimbolos.h"

class IRBuilder : public Visitor {
    IRProgram&     prog;
    TablaSimbolos* currentTS;
    IRArg          lastResult;   // resultado devuelto por los visit de expresión

    // Evalúa un nodo expresión y devuelve su IRArg resultado
    IRArg eval(ExprNode* node) {
        node->accept(this);
        return lastResult;
    }

public:
    IRBuilder(IRProgram& p, TablaSimbolos* ts)
        : prog(p), currentTS(ts) {}

    // ------------------------------------------------------------------ //
    //  Nodos de programa y bloque
    // ------------------------------------------------------------------ //

    void visit(ProgramNode* node) override {
        if (node->root) node->root->accept(this);
        prog.emit(IR_HALT);
    }

    void visit(BlockNode* node) override {
        TablaSimbolos* old = currentTS;
        if (node->symbols) currentTS = node->symbols;
        for (const auto& s : node->statements)
            if (s) s->accept(this);
        currentTS = old;
    }

    // [IR-6] IR para funciones
    void visit(MethodNode* node) override {
        prog.emit(IR_FUNC_BEGIN, IRArg::func(node->name));
        if (node->body) node->body->accept(this);
        prog.emit(IR_FUNC_END, IRArg::func(node->name));
    }

    // ------------------------------------------------------------------ //
    //  Sentencias
    // ------------------------------------------------------------------ //

    void visit(AssignNode* node) override {
        IRArg val = eval(node->value.get());

        // Resuelve la dirección del destino desde la tabla de símbolos
        Simbolo* sym = currentTS ? currentTS->get(node->target->name) : nullptr;
        int addr = sym ? (int)sym->dir : node->target->dir;
        int type = sym ? (int)sym->tipo : node->target->type;

        IRArg dst = IRArg::var(node->target->name, addr, type);
        prog.emit(IR_COPY, val, IRArg{}, dst, type);
    }

    void visit(PrintNode* node) override {
        IRArg val = eval(node->expr.get());
        if (node->expr->type == REAL)
            prog.emit(IR_PRINT_REAL, val);
        else
            prog.emit(IR_PRINT_INT, val);
        if (node->isPrintln)
            prog.emit(IR_PRINT_NL);
    }

    // [IR-6] Return
    void visit(ReturnNode* node) override {
        if (node->expr) {
            IRArg val = eval(node->expr.get());
            prog.emit(IR_RETURN, val, IRArg{}, IRArg{}, node->expr->type);
        } else {
            prog.emit(IR_RETURN);
        }
    }

    // [IR-5] Salto condicional: if
    void visit(IfNode* node) override {
        IRArg cond = eval(node->condition.get());

        if (node->elsePart) {
            std::string elseL = prog.newLabel();
            std::string endL  = prog.newLabel();

            prog.emit(IR_JZ, cond, IRArg::label(elseL));
            if (node->thenPart) node->thenPart->accept(this);
            prog.emit(IR_JMP, IRArg::label(endL));
            prog.emit(IR_LABEL, IRArg::label(elseL));
            node->elsePart->accept(this);
            prog.emit(IR_LABEL, IRArg::label(endL));
        } else {
            std::string endL = prog.newLabel();
            prog.emit(IR_JZ, cond, IRArg::label(endL));
            if (node->thenPart) node->thenPart->accept(this);
            prog.emit(IR_LABEL, IRArg::label(endL));
        }
    }

    // [IR-5] Salto condicional: while
    void visit(WhileNode* node) override {
        std::string startL = prog.newLabel();
        std::string endL   = prog.newLabel();

        prog.emit(IR_LABEL, IRArg::label(startL));
        IRArg cond = eval(node->condition.get());
        prog.emit(IR_JZ, cond, IRArg::label(endL));
        if (node->body) node->body->accept(this);
        prog.emit(IR_JMP, IRArg::label(startL));
        prog.emit(IR_LABEL, IRArg::label(endL));
    }

    // ------------------------------------------------------------------ //
    //  Expresiones
    // ------------------------------------------------------------------ //

    // [IR-4] Expresiones aritméticas y lógicas binarias
    void visit(BinaryExprNode* node) override {
        IRArg l = eval(node->left.get());
        IRArg r = eval(node->right.get());

        int resultType = node->type;
        IRArg t = prog.newTemp(resultType);

        IROpcode op;
        const std::string& o = node->op;
        if      (o == "+")  op = IR_ADD;
        else if (o == "-")  op = IR_SUB;
        else if (o == "*")  op = IR_MUL;
        else if (o == "/")  op = IR_DIV;
        else if (o == "%")  op = IR_MOD;
        else if (o == "&&") op = IR_AND;
        else if (o == "||") op = IR_OR;
        else if (o == "==") op = IR_EQ;
        else if (o == "!=") op = IR_NEQ;
        else if (o == "<")  op = IR_LT;
        else if (o == "<=") op = IR_LTE;
        else if (o == ">")  op = IR_GT;
        else                op = IR_GTE;

        prog.emit(op, l, r, t, resultType);
        lastResult = t;
    }

    // [IR-4] Expresiones unarias
    void visit(UnaryExprNode* node) override {
        IRArg val = eval(node->expr.get());
        IRArg t   = prog.newTemp(node->type);

        if (node->op == "-")
            prog.emit(IR_NEG, val, IRArg{}, t, node->type);
        else
            prog.emit(IR_NOT, val, IRArg{}, t, node->type);

        lastResult = t;
    }

    void visit(IdentifierNode* node) override {
        lastResult = IRArg::var(node->name, node->dir, node->type);
    }

    void visit(IntLiteralNode* node) override {
        lastResult = IRArg::constInt(node->value);
    }

    void visit(FloatLiteralNode* node) override {
        lastResult = IRArg::constReal(node->value);
    }

    void visit(BoolLiteralNode* node) override {
        lastResult = IRArg::constInt(node->value ? 1 : 0);
    }

    // [BND-8] Llamada a función: emite IR_CALL
    void visit(CallNode* node) override {
        IRArg result = IRArg::none();
        if (node->type != -1)
            result = prog.newTemp(node->type);
        prog.emit(IR_CALL, IRArg::func(node->name), IRArg{}, result, node->type);
        lastResult = result;
    }

    // [BND-12] Lectura de stdin: emite IR_READ_INT o IR_READ_REAL
    void visit(ReadNode* node) override {
        int type = node->isDouble ? REAL : ENTERO;
        IRArg t = prog.newTemp(type);
        IROpcode op = node->isDouble ? IR_READ_REAL : IR_READ_INT;
        prog.emit(op, IRArg{}, IRArg{}, t, type);
        lastResult = t;
    }
};

#endif
