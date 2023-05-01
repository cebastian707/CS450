//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_EXPRNODE_HPP
#define APYTHONINTERPRETER_EXPRNODE_HPP


#include "Token.hpp"
#include "SymTab.hpp"
#include "TypeDescriptor.hpp"
// Classes in this file define the internal representation of arithmetic expressions.


// An ArithExprNode serves as the base class (super class) for arithmetic expression.
// It forces the derived classes (subclasses) to implement two functions, print and
// evaluate.

class ExprNode {
public:
    explicit ExprNode(Token token);
    Token token();
    virtual void print() = 0;
    virtual TypeDescriptor* evaluate(SymTab &symTab);

private:
    Token _token;

protected:
    bool debug = false;
};


// An InfixExprNode is useful to represent binary arithmetic operators.
class InfixExprNode: public ExprNode {  // An expression tree node.

public:
    explicit InfixExprNode(Token tk);

    ExprNode *&left();
    ExprNode *&right();
    void print () override;
    TypeDescriptor* evaluate(SymTab &symTab) override;

private:
    ExprNode *_left, *_right;
};

// WholeNumber is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.
class WholeNumber: public ExprNode {
public:
    explicit WholeNumber(Token token);
    void print() override;
    TypeDescriptor* evaluate(SymTab &symTab) override;
};

// Varialbe is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class Variable: public ExprNode {
public:
    explicit Variable(Token token);
    void print() override;
    TypeDescriptor* evaluate(SymTab &symTab) override;
};

class StringLiteral : public ExprNode {
public:
    explicit StringLiteral(Token token);
    void print() override;
    TypeDescriptor* evaluate(SymTab &symTab)override;
};


class DoubleNumber: public ExprNode {
public:
    explicit DoubleNumber(Token token);
    void print() override;
    TypeDescriptor* evaluate(SymTab &symTab) override;
};
#endif //APYTHONINTERPRETER_EXPRNODE_HPP
