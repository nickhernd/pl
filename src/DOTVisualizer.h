#ifndef _DOT_VISUALIZER_H
#define _DOT_VISUALIZER_H

#include "ASTNodes.h"
#include <iostream>
#include <string>
#include <map>

class DOTVisualizer : public Visitor {
    int nodeCount = 0;
    std::string newNode() {
        return "node" + std::to_string(nodeCount++);
    }

    void addEdge(const std::string& from, const std::string& to) {
        std::cout << "  " << from << " -> " << to << ";" << std::endl;
    }

    void setLabel(const std::string& node, const std::string& label) {
        std::cout << "  " << node << " [label=\"" << label << "\"];" << std::endl;
    }

    std::string lastNode;

public:
    void print(Node* root) {
        std::cout << "digraph AST {" << std::endl;
        std::cout << "  node [shape=box];" << std::endl;
        if (root) root->accept(this);
        std::cout << "}" << std::endl;
    }

    void visit(ProgramNode* node) override {
        std::string current = newNode();
        setLabel(current, "Program");
        if (node->root) {
            node->root->accept(this);
            addEdge(current, lastNode);
        }
        lastNode = current;
    }

    void visit(BlockNode* node) override {
        std::string current = newNode();
        setLabel(current, "Block");
        for (const auto& s : node->statements) {
            if (s) {
                s->accept(this);
                addEdge(current, lastNode);
            }
        }
        lastNode = current;
    }

    void visit(MethodNode* node) override {
        std::string current = newNode();
        setLabel(current, "Method: " + node->name);
        if (node->body) {
            node->body->accept(this);
            addEdge(current, lastNode);
        }
        lastNode = current;
    }

    void visit(AssignNode* node) override {
        std::string current = newNode();
        setLabel(current, "Assign (=)");
        node->target->accept(this);
        addEdge(current, lastNode);
        node->value->accept(this);
        addEdge(current, lastNode);
        lastNode = current;
    }

    void visit(PrintNode* node) override {
        std::string current = newNode();
        setLabel(current, node->isPrintln ? "Println" : "Print");
        node->expr->accept(this);
        addEdge(current, lastNode);
        lastNode = current;
    }

    void visit(ReturnNode* node) override {
        std::string current = newNode();
        setLabel(current, "Return");
        if (node->expr) {
            node->expr->accept(this);
            addEdge(current, lastNode);
        }
        lastNode = current;
    }

    void visit(IfNode* node) override {
        std::string current = newNode();
        setLabel(current, "If");
        node->condition->accept(this);
        addEdge(current, lastNode);
        node->thenPart->accept(this);
        addEdge(current, lastNode);
        if (node->elsePart) {
            node->elsePart->accept(this);
            addEdge(current, lastNode);
        }
        lastNode = current;
    }

    void visit(WhileNode* node) override {
        std::string current = newNode();
        setLabel(current, "While");
        node->condition->accept(this);
        addEdge(current, lastNode);
        node->body->accept(this);
        addEdge(current, lastNode);
        lastNode = current;
    }

    void visit(BinaryExprNode* node) override {
        std::string current = newNode();
        setLabel(current, "Binary Op: " + node->op);
        node->left->accept(this);
        addEdge(current, lastNode);
        node->right->accept(this);
        addEdge(current, lastNode);
        lastNode = current;
    }

    void visit(UnaryExprNode* node) override {
        std::string current = newNode();
        setLabel(current, "Unary Op: " + node->op);
        node->expr->accept(this);
        addEdge(current, lastNode);
        lastNode = current;
    }

    void visit(IdentifierNode* node) override {
        lastNode = newNode();
        setLabel(lastNode, "Id: " + node->name);
    }

    void visit(IntLiteralNode* node) override {
        lastNode = newNode();
        setLabel(lastNode, "Int: " + std::to_string(node->value));
    }

    void visit(FloatLiteralNode* node) override {
        lastNode = newNode();
        setLabel(lastNode, "Float: " + std::to_string(node->value));
    }

    void visit(BoolLiteralNode* node) override {
        lastNode = newNode();
        setLabel(lastNode, "Bool: " + std::string(node->value ? "true" : "false"));
    }
};

#endif
