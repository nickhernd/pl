#ifndef _NODE_H
#define _NODE_H

#include "Visitor.h"
#include <vector>
#include <string>

class Node {
public:
    int line;
    int column;

    Node(int l = 0, int c = 0) : line(l), column(c) {}
    virtual ~Node() {}
    virtual void accept(Visitor* visitor) = 0;
};

// Intermediate base class for Statements
class StmtNode : public Node {
public:
    using Node::Node;
};

// Intermediate base class for Expressions
class ExprNode : public Node {
public:
    int type; // From TablaTipos
    int dir;  // Memory address/offset
    ExprNode(int l = 0, int c = 0) : Node(l, c), type(-1), dir(-1) {}
};

#endif
