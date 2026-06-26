#ifndef _VISITOR_H
#define _VISITOR_H

// Forward declarations of Node types
class Node;
class ProgramNode;
class StmtNode;
class ExprNode;
class BinaryExprNode;
class UnaryExprNode;
class IdentifierNode;
class IntLiteralNode;
class FloatLiteralNode;
class BoolLiteralNode;
class AssignNode;
class IfNode;
class WhileNode;
class BlockNode;
class PrintNode;
class ReturnNode;
class MethodNode;
class CallNode;
class ReadNode;
class ResultNode;

class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visit(ProgramNode* node) = 0;
    virtual void visit(BlockNode* node) = 0;
    virtual void visit(MethodNode* node) = 0;
    virtual void visit(AssignNode* node) = 0;
    virtual void visit(PrintNode* node) = 0;
    virtual void visit(ReturnNode* node) = 0;
    virtual void visit(IfNode* node) = 0;
    virtual void visit(WhileNode* node) = 0;
    virtual void visit(BinaryExprNode* node) = 0;
    virtual void visit(UnaryExprNode* node) = 0;
    virtual void visit(IdentifierNode* node) = 0;
    virtual void visit(IntLiteralNode* node) = 0;
    virtual void visit(FloatLiteralNode* node) = 0;
    virtual void visit(BoolLiteralNode* node) = 0;
    virtual void visit(CallNode* node) = 0;
    virtual void visit(ReadNode* node) = 0;
    virtual void visit(ResultNode* node) = 0;
};

#endif
