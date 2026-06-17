#ifndef _CODE_GENERATOR_H
#define _CODE_GENERATOR_H

#include "ASTNodes.h"
#include "TablaSimbolos.h"
#include <iostream>
#include <string>
#include <vector>

class CodeGenerator : public Visitor {
    int labelCount = 0;
    std::string newLabel() {
        return ".L" + std::to_string(labelCount++);
    }

    void emit(const std::string& instr) {
        std::cout << "    " << instr << std::endl;
    }

    void emitLabel(const std::string& label) {
        std::cout << label << ":" << std::endl;
    }

    // Map a symbol's directory to a stack offset
    // For simplicity, we assume 8 bytes per variable
    int getOffset(int dir) {
        return -(dir + 1) * 8;
    }

public:
    void generate(Node* root, int stackSize) {
        // Data section for printf strings
        std::cout << ".section .data" << std::endl;
        std::cout << "format_int: .string \"%d\\n\"" << std::endl;
        std::cout << "format_float: .string \"%g\\n\"" << std::endl;
        std::cout << "" << std::endl;

        std::cout << ".section .text" << std::endl;
        std::cout << ".globl main" << std::endl;
        std::cout << "" << std::endl;
        
        if (root) root->accept(this);
    }

    void visit(ProgramNode* node) override {
        emitLabel("main");
        emit("pushq %rbp");
        emit("movq %rsp, %rbp");
        
        // Reserve space for variables (round up to 16-byte alignment)
        // We'll calculate actual need or just use a safe buffer for now
        // A better way is to pass next_dir here.
        emit("subq $4096, %rsp"); 

        if (node->root) node->root->accept(this);

        emit("movq %rbp, %rsp");
        emit("popq %rbp");
        emit("ret");
    }

    void visit(BlockNode* node) override {
        for (const auto& s : node->statements) if (s) s->accept(this);
    }

    void visit(AssignNode* node) override {
        // Evaluate value into %rax
        node->value->accept(this);
        
        // Target address is stored in node->target->dir
        // We need to fetch the offset
        int offset = getOffset(node->target->dir);
        emit("movq %rax, " + std::to_string(offset) + "(%rbp)");
    }

    void visit(IdentifierNode* node) override {
        // Load variable from stack into %rax
        int offset = getOffset(node->dir);
        emit("movq " + std::to_string(offset) + "(%rbp), %rax");
    }

    void visit(IntLiteralNode* node) override {
        emit("movq $" + std::to_string(node->value) + ", %rax");
    }

    void visit(FloatLiteralNode* node) override {
        // Floating point is more complex in x86-64 (needs XMM registers)
        // For a first pass, let's focus on Integers or just emit a placeholder
        emit("# FloatLiteral not yet fully implemented in x86");
    }

    void visit(BoolLiteralNode* node) override {
        emit("movq $" + std::string(node->value ? "1" : "0") + ", %rax");
    }

    void visit(BinaryExprNode* node) override {
        node->left->accept(this);
        emit("pushq %rax");
        node->right->accept(this);
        emit("movq %rax, %rbx");
        emit("popq %rax");

        if (node->op == "+") emit("addq %rbx, %rax");
        else if (node->op == "-") emit("subq %rbx, %rax");
        else if (node->op == "*") emit("imulq %rbx, %rax");
        else if (node->op == "/") {
            emit("cqto"); // Sign extend %rax into %rdx:%rax
            emit("idivq %rbx");
        }
        // Comparisons
        else if (node->op == "==" || node->op == "!=" || node->op == "<" || node->op == "<=" || node->op == ">" || node->op == ">=") {
            emit("cmpq %rbx, %rax");
            if (node->op == "==") emit("sete %al");
            else if (node->op == "!=") emit("setne %al");
            else if (node->op == "<") emit("setl %al");
            else if (node->op == "<=") emit("setle %al");
            else if (node->op == ">") emit("setg %al");
            else if (node->op == ">=") emit("setge %al");
            emit("movzbq %al, %rax");
        }
    }

    void visit(UnaryExprNode* node) override {
        node->expr->accept(this);
        if (node->op == "-") emit("negq %rax");
        else if (node->op == "!") {
            emit("cmpq $0, %rax");
            emit("sete %al");
            emit("movzbq %al, %rax");
        }
    }

    void visit(PrintNode* node) override {
        node->expr->accept(this);
        // %rdi = format string
        // %rsi = value to print
        emit("movq %rax, %rsi");
        emit("leaq format_int(%rip), %rdi");
        emit("movl $0, %eax"); // Number of vector registers used
        emit("call printf@PLT");
    }

    void visit(IfNode* node) override {
        std::string elseLabel = newLabel();
        std::string endLabel = newLabel();

        node->condition->accept(this);
        emit("cmpq $0, %rax");
        emit("je " + elseLabel);
        
        node->thenPart->accept(this);
        emit("jmp " + endLabel);

        emitLabel(elseLabel);
        if (node->elsePart) node->elsePart->accept(this);

        emitLabel(endLabel);
    }

    void visit(WhileNode* node) override {
        std::string startLabel = newLabel();
        std::string endLabel = newLabel();

        emitLabel(startLabel);
        node->condition->accept(this);
        emit("cmpq $0, %rax");
        emit("je " + endLabel);

        node->body->accept(this);
        emit("jmp " + startLabel);

        emitLabel(endLabel);
    }
};

#endif
