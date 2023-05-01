//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_STATEMENTS_HPP
#define APYTHONINTERPRETER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ExprNode.hpp"
#include "SymTab.hpp"

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
    ForStatement() {}
    ForStatement(AssignmentStatement* initStmt, ExprNode* condExpr, AssignmentStatement* updateExpr, Statements* body) :
            _initStatement(initStmt), _conditionExpression(condExpr), _updateExpression(updateExpr), _body(body) {}

    ForStatement(Statement *pStatement, ExprNode *pNode, Statement *pStatement1, Statements *pStatements) {
        _initStatement = dynamic_cast<AssignmentStatement *>(pStatement);
        _conditionExpression = pNode;
        _updateExpression = dynamic_cast<AssignmentStatement *>(pStatement1);
        _body = pStatements;
    }

    AssignmentStatement*& initStatement() { return _initStatement; }
    ExprNode*& conditionExpression() { return _conditionExpression; }
    AssignmentStatement*& updateExpression() { return _updateExpression; }
    Statements*& body() { return _body; }

    virtual void print() {
        std::cout << "for ( "; _initStatement->print();std::cout << ";  "; _conditionExpression->print(); std::cout << "; ";_updateExpression->print(); std::cout << ") {";
        _body->print();
        std::cout << "}";
    }

    virtual void evaluate(SymTab& symTab) {
        _initStatement->evaluate(symTab);

        // Ensure the condition expression returns an integer value
        TypeDescriptor* conditionResult = _conditionExpression->evaluate(symTab);
        if (conditionResult->type() != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate: Type mismatch, expected INTEGER" << std::endl;
            exit(1);
        }

        while (dynamic_cast<NumberDescriptor*>(conditionResult)->value.intValue != 0) {
            _body->evaluate(symTab);
            _updateExpression->evaluate(symTab);

            // Re-evaluate the condition expression to check if the loop should continue
            conditionResult = _conditionExpression->evaluate(symTab);
            if (conditionResult->type() != TypeDescriptor::INTEGER) {
                std::cout << "ForStatement::evaluate: Type mismatch, expected INTEGER" << std::endl;
                exit(1);
            }
        }
    }


private:
    AssignmentStatement* _initStatement;
    ExprNode* _conditionExpression;
    AssignmentStatement* _updateExpression;
    Statements* _body;
};






#endif //APYTHONINTERPRETER_STATEMENTS_HPP
