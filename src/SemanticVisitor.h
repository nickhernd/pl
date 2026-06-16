#ifndef _SEMANTIC_VISITOR_H
#define _SEMANTIC_VISITOR_H

#include "ASTNodes.h"
#include "TablaSimbolos.h"
#include "TablaTipos.h"
#include <iostream>

class SemanticVisitor : public Visitor {
    TablaSimbolos* currentTS;
    TablaTipos* tt;
    bool hasErrors = false;

    void error(int line, int col, const std::string& msg) {
        std::cerr << "Semantic Error (" << line << "," << col << "): " << msg << std::endl;
        hasErrors = true;
    }

public:
    SemanticVisitor(TablaSimbolos* ts, TablaTipos* types) : currentTS(ts), tt(types) {}

    bool success() const { return !hasErrors; }

    void visit(ProgramNode* node) override { if (node->root) node->root->accept(this); }

    void visit(BlockNode* node) override {
        TablaSimbolos* oldTS = currentTS;
        if (node->symbols) currentTS = node->symbols;
        for (auto s : node->statements) if (s) s->accept(this);
        currentTS = oldTS;
    }

    void visit(AssignNode* node) override {
        node->target->accept(this);
        node->value->accept(this);
        if (node->target->type != -1 && node->value->type != -1) {
            if (node->target->type != node->value->type) {
                if (node->target->type == REAL && node->value->type == ENTERO) {
                    // OK: Promotion
                } else {
                    error(node->line, node->column, "Incompatible types in assignment");
                }
            }
        }
    }

    void visit(IfNode* node) override {
        node->condition->accept(this);
        if (node->condition->type != LOGICO && node->condition->type != -1) {
            error(node->condition->line, node->condition->column, "If condition must be boolean");
        }
        if (node->thenPart) node->thenPart->accept(this);
        if (node->elsePart) node->elsePart->accept(this);
    }

    void visit(WhileNode* node) override {
        node->condition->accept(this);
        if (node->condition->type != LOGICO && node->condition->type != -1) {
            error(node->condition->line, node->condition->column, "While condition must be boolean");
        }
        if (node->body) node->body->accept(this);
    }

    void visit(BinaryExprNode* node) override {
        node->left->accept(this);
        node->right->accept(this);
        if (node->left->type == -1 || node->right->type == -1) { node->type = -1; return; }

        if (node->op == "||" || node->op == "&&") {
            if (node->left->type == LOGICO && node->right->type == LOGICO) node->type = LOGICO;
            else { error(node->line, node->column, "Logical operators require boolean operands"); node->type = -1; }
        } else if (node->op == "==" || node->op == "!=" || node->op == "<" || node->op == "<=" || node->op == ">" || node->op == ">=") {
            if ((node->left->type == ENTERO || node->left->type == REAL) && (node->right->type == ENTERO || node->right->type == REAL)) node->type = LOGICO;
            else if (node->left->type == LOGICO && node->right->type == LOGICO) node->type = LOGICO;
            else { error(node->line, node->column, "Invalid operand types for comparison"); node->type = -1; }
        } else {
            if (node->left->type == REAL || node->right->type == REAL) node->type = REAL;
            else if (node->left->type == ENTERO && node->right->type == ENTERO) node->type = ENTERO;
            else { error(node->line, node->column, "Invalid operand types for arithmetic operator " + node->op); node->type = -1; }
        }
    }

    void visit(UnaryExprNode* node) override {
        node->expr->accept(this);
        if (node->expr->type == -1) { node->type = -1; return; }
        if (node->op == "!") {
            if (node->expr->type == LOGICO) node->type = LOGICO;
            else { error(node->line, node->column, "Logical NOT requires boolean operand"); node->type = -1; }
        } else {
            // Unary minus/plus
            if (node->expr->type == ENTERO || node->expr->type == REAL) node->type = node->expr->type;
            else { error(node->line, node->column, "Numeric operator requires numeric operand"); node->type = -1; }
        }
    }

    void visit(IdentifierNode* node) override {
        Simbolo* s = currentTS->get(node->name);
        if (!s) { error(node->line, node->column, "Identifier '" + node->name + "' not declared"); node->type = -1; }
        else node->type = s->tipo;
    }

    void visit(IntLiteralNode* node) override { node->type = ENTERO; }
    void visit(FloatLiteralNode* node) override { node->type = REAL; }
    void visit(BoolLiteralNode* node) override { node->type = LOGICO; }
};

#endif
