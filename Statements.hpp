//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_STATEMENTS_HPP
#define APYTHONINTERPRETER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ExprNode.hpp"
#include "SymTab.hpp"
#include "Range.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
    Statement();
    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.
class Statements {
public:
    Statements();

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);

    void print();

private:
    std::vector<Statement *> _statements;
};

// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.
class AssignmentStatement : public Statement {
public:
    AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);

    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
};

class PrintStatement : public Statement {
public:
    PrintStatement();
    PrintStatement(std::string lhsVar, std::vector<ExprNode*> exprs) : _lhsVariable(lhsVar), _expressions(exprs) {}

    std::string& lhsVariable();
    std::vector<ExprNode*>& expressions() { return _expressions; }

    virtual void print() {
        std::cout << "PRINT " << _lhsVariable << std::endl;
        for (auto expr : _expressions) {
            expr->print();
        }
    }

    virtual void evaluate(SymTab& symTab) {
        for (auto expr : _expressions) {
            TypeDescriptor* desc = expr->evaluate(symTab);
            if (desc->type() == TypeDescriptor::INTEGER) {
                std::cout << dynamic_cast<NumberDescriptor*>(desc)->value.intValue << " " <<std::endl;
                std::cout << " " << std::endl;
            } else if (desc->type() == TypeDescriptor::STRING) {
                std::cout << dynamic_cast<StringDescriptor*>(desc)->str << " ";
            } else if (desc->type() == TypeDescriptor::DOUBLE){
                std::cout << dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue << " " <<std::endl;
            } else if (desc->type() == TypeDescriptor::BOOL){
                short bool_value = dynamic_cast<NumberDescriptor*>(desc)->value.boolValue;
                if (bool_value == 0) {
                    std::cout << "False"<< std::endl;
                } else{
                    std::cout << "True" << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }

private:
    std::string _lhsVariable;
    std::vector<ExprNode*> _expressions;
};

class ForStatement : public Statement {
public:
    ForStatement();
    ForStatement(Token loopVar, std::vector<ExprNode*> rangeArgs, Statements *body);

    Token &loopVar();
    std::vector<ExprNode*> &rangeArgs();
    Statements *&body();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    Token _loopVar;
    std::vector<ExprNode*> _rangeArgs;
    Statements *_body;
};



class IfStatement : public Statement {
public:
    IfStatement();
    IfStatement(std::vector<ExprNode*> conditions, std::vector<Statements*> bodies);

    std::vector<ExprNode*> &conditions();
    std::vector<Statements*> &bodies();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::vector<ExprNode*> _conditions;
    std::vector<Statements*> _bodies;
};


#endif //APYTHONINTERPRETER_STATEMENTS_HPP
