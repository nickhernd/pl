#ifndef _AST_VISUALIZER_H
#define _AST_VISUALIZER_H

#include "ASTNodes.h"
#include <iostream>
#include <string>

class ASTVisualizer : public Visitor {
    int indentLevel = 0;
    void printIndent() {
        for (int i = 0; i < indentLevel; ++i) std::cout << "  ";
    }

public:
    void visit(ProgramNode* node) override {
        std::cout << "ProgramNode" << std::endl;
        indentLevel++;
        if (node->root) node->root->accept(this);
        indentLevel--;
    }

    void visit(BlockNode* node) override {
        printIndent();
        std::cout << "BlockNode (" << node->statements.size() << " statements)" << std::endl;
        indentLevel++;
        for (auto s : node->statements) if (s) s->accept(this);
        indentLevel--;
    }

    void visit(AssignNode* node) override {
        printIndent();
        std::cout << "AssignNode" << std::endl;
        indentLevel++;
        node->target->accept(this);
        node->value->accept(this);
        indentLevel--;
    }

    void visit(IfNode* node) override {
        printIndent(); std::cout << "IfNode" << std::endl;
        indentLevel++;
        printIndent(); std::cout << "Condition:" << std::endl;
        indentLevel++; node->condition->accept(this); indentLevel--;
        printIndent(); std::cout << "Then:" << std::endl;
        indentLevel++; node->thenPart->accept(this); indentLevel--;
        if (node->elsePart) {
            printIndent(); std::cout << "Else:" << std::endl;
            indentLevel++; node->elsePart->accept(this); indentLevel--;
        }
        indentLevel--;
    }

    void visit(WhileNode* node) override {
        printIndent(); std::cout << "WhileNode" << std::endl;
        indentLevel++;
        printIndent(); std::cout << "Condition:" << std::endl;
        indentLevel++; node->condition->accept(this); indentLevel--;
        printIndent(); std::cout << "Body:" << std::endl;
        indentLevel++; node->body->accept(this); indentLevel--;
        indentLevel--;
    }

    void visit(BinaryExprNode* node) override {
        printIndent(); std::cout << "BinaryExprNode (" << node->op << ")" << std::endl;
        indentLevel++;
        node->left->accept(this);
        node->right->accept(this);
        indentLevel--;
    }

    void visit(IdentifierNode* node) override {
        printIndent(); std::cout << "IdentifierNode: " << node->name << std::endl;
    }

    void visit(IntLiteralNode* node) override {
        printIndent(); std::cout << "IntLiteralNode: " << node->value << std::endl;
    }

    void visit(FloatLiteralNode* node) override {
        printIndent(); std::cout << "FloatLiteralNode: " << node->value << std::endl;
    }

    void visit(BoolLiteralNode* node) override {
        printIndent(); std::cout << "BoolLiteralNode: " << (node->value ? "true" : "false") << std::endl;
    }
};

#endif
