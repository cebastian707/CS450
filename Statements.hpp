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

    ForStatement(ExprNode* variable, std::vector<ExprNode*> iterable, Statements* body) :
            _variable(variable), _iterable(iterable), _body(body) {}

    ExprNode*& variable() { return _variable; }
    std::vector<ExprNode*>& iterable() { return _iterable; }
    Statements*& body() { return _body; }


    virtual void print() {
        std::cout << "for ";
        _variable->print();
        std::cout << " in ";
        for (auto it : _iterable) {
            it->print();
            std::cout << ",";
        }
        std::cout << "): " << std::endl;
        _body->print();
    }

    virtual void evaluate(SymTab& symTab) {
        // Set the initial value of the loop variable to 0
        TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::INTEGER);


        if (_iterable.size()-1 == 0) {
            //set i equal to zero
            dynamic_cast<NumberDescriptor*>(desc)->value.intValue = 0;
            symTab.setValueFor(_variable->token().getName(), desc);

            //range value get it
            int range = dynamic_cast<NumberDescriptor *>(_iterable[0]->evaluate(symTab))->value.intValue;

            //initlaize the range value
            Range *rangeInstance = new Range(range);


            // Loop through the range instance values
            while (rangeInstance->condition()) {
                // Get the next value from the range instance and set it to the loop variable
                int loopVal = rangeInstance->next();
                dynamic_cast<NumberDescriptor *>(desc)->value.intValue = loopVal;

                // Evaluate the loop body
                _body->evaluate(symTab);

                // Evaluate the loop variable
                symTab.setValueFor(_variable->token().getName(), desc);
            }

        }

        else if (_iterable.size()-1 == 1){
            //range value start value
            int start = dynamic_cast<NumberDescriptor *>(_iterable[0]->evaluate(symTab))->value.intValue;

            dynamic_cast<NumberDescriptor*>(desc)->value.intValue = start;
            symTab.setValueFor(_variable->token().getName(), desc);


            //get the end value of the range
            int end = dynamic_cast<NumberDescriptor *>(_iterable[1]->evaluate(symTab))->value.intValue;

            //initlaize the range value
            Range *rangeInstance = new Range(start,end);

            // Loop through the range instance values
            while (rangeInstance->condition()) {
                // Get the next value from the range instance and set it to the loop variable
                int loopVal = rangeInstance->next();

                dynamic_cast<NumberDescriptor *>(desc)->value.intValue = loopVal;

                // Evaluate the loop body
                _body->evaluate(symTab);

                // Evaluate the loop variable
                symTab.setValueFor(_variable->token().getName(), desc);
            }


        }

        else if (_iterable.size()-1 == 2){
            //range value start value
            int start = dynamic_cast<NumberDescriptor *>(_iterable[0]->evaluate(symTab))->value.intValue;


            //set the i variable to the intial value
            dynamic_cast<NumberDescriptor*>(desc)->value.intValue = start;
            symTab.setValueFor(_variable->token().getName(), desc);




            //get the end value of the range
            int end = dynamic_cast<NumberDescriptor *>(_iterable[1]->evaluate(symTab))->value.intValue;

            //get the step value
            int step  = dynamic_cast<NumberDescriptor *>(_iterable[2]->evaluate(symTab))->value.intValue;


            //initlaize the range value
            Range *rangeInstance = new Range(start,end,step);

            // Loop through the range instance values
            while (rangeInstance->condition()) {
                // Get the next value from the range instance and set it to the loop variable
                int loopVal = rangeInstance->next();
                dynamic_cast<NumberDescriptor *>(desc)->value.intValue = loopVal;

                // Evaluate the loop body
                _body->evaluate(symTab);

                // Evaluate the loop variable
                symTab.setValueFor(_variable->token().getName(), desc);
            }
        } else{
            std::cout << "Range only takes three values"<<std::endl;
        }
    }




private:
    ExprNode* _variable;
    std::vector<ExprNode*> _iterable;
    Statements* _body;
};
#endif //APYTHONINTERPRETER_STATEMENTS_HPP
