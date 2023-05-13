//
// Created by Ali Kooshesh on 4/4/23.
//

#include "Statements.hpp"

// Statement
Statement::Statement() {}

// Statements

Statements::Statements() {}

void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    for (auto s: _statements)
        s->print();
        std::cout<<std::endl;
}

void Statements::evaluate(SymTab &symTab) {
    for (auto s: _statements)
        s->evaluate(symTab);
}

// AssignmentStatement

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
        auto rhs = rhsExpression()->evaluate(symTab);
        symTab.setValueFor(lhsVariable(), reinterpret_cast<TypeDescriptor *>(rhs));

}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}

void AssignmentStatement::print() {
    std::cout << _lhsVariable << " = ";
    _rhsExpression->print();
    std::cout << std::endl;
}


std::string &PrintStatement::lhsVariable() { return _lhsVariable; }

// ForStatement

ForStatement::ForStatement() : _loopVar{Token()}, _rangeArgs{nullptr}, _body{nullptr} {}

ForStatement::ForStatement(Token loopVar, std::vector<ExprNode*> rangeArgs, Statements *body):
        _loopVar{loopVar}, _rangeArgs{rangeArgs}, _body{body} {}

void ForStatement::evaluate(SymTab &symTab) {
    TypeDescriptor* init;
    TypeDescriptor* end;
    TypeDescriptor* step;
    TypeDescriptor::types type;
    std::vector<ExprNode*> args = rangeArgs();
    Range* range;

    if (args.size() == 1) {
        end = args[0]->evaluate(symTab);
        type = end->type();
        if (type != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate The first argument in range must be an integer\n";
            exit(1);
        }
        range = new Range(dynamic_cast<NumberDescriptor*>(end)->value.intValue);
    } else if (args.size() == 2) {
        init = args[0]->evaluate(symTab);
        type = init->type();
        if (type != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate The first argument in range must be an integer\n";
            exit(1);
        }
        end = args[1]->evaluate(symTab);
        type = end->type();
        if (type != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate The second argument in range must be an integer\n";
            exit(1);
        }
        range = new Range(dynamic_cast<NumberDescriptor*>(init)->value.intValue,
                          dynamic_cast<NumberDescriptor*>(end)->value.intValue);
    } else {
        init = args[0]->evaluate(symTab);
        type = init->type();
        if (type != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate The first argument in range must be an integer\n";
            exit(1);
        }
        end = args[1]->evaluate(symTab);
        type = end->type();
        if (type != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate The second argument in range must be an integer\n";
            exit(1);
        }
        step = args[2]->evaluate(symTab);
        type = step->type();
        if (type != TypeDescriptor::INTEGER) {
            std::cout << "ForStatement::evaluate The third argument in range must be an integer\n";
            exit(1);
        }
        range = new Range(dynamic_cast<NumberDescriptor*>(init)->value.intValue,
                          dynamic_cast<NumberDescriptor*>(end)->value.intValue,
                          dynamic_cast<NumberDescriptor*>(step)->value.intValue);
    }
    Token val;
    std::string varName = loopVar().getName();
    while( range->condition() ) {
        val.setWholeNumber(range->next());
        symTab.setValueFor(varName, WholeNumber(val).evaluate(symTab));
        body()->evaluate(symTab);
    }
}

Token &ForStatement::loopVar() {
    return _loopVar;
}

std::vector<ExprNode*> &ForStatement::rangeArgs() {
    return _rangeArgs;
}

Statements *&ForStatement::body() {
    return _body;
}

void ForStatement::print() {
    std::cout << "for ";
    _loopVar.print();
    std::cout << " in range(";
    _rangeArgs[0]->print();
    for (int i = 1; i < _rangeArgs.size(); i++) {
        std::cout << ", ";
        _rangeArgs[i]->print();
    }
    std::cout << "):" << std::endl;
    _body->print();
}
// IfStatement
IfStatement::IfStatement() : _conditions{nullptr}, _bodies{nullptr} {}

IfStatement::IfStatement(std::vector<ExprNode*> conditions, std::vector<Statements*> bodies): _conditions{conditions},
                                                                                              _bodies{bodies} {}

void IfStatement::evaluate(SymTab &symTab) {
    bool done = false;
    int i;
    int size = conditions().size();
    for (i = 0; i < size; i++) {
        TypeDescriptor *cond = conditions()[i]->evaluate(symTab);
        if (cond->type() != TypeDescriptor::INTEGER) {
            std::cout << "IfStatement::evaluate The condition must evaluate to an integer\n";
            exit(1);
        }
        int val = dynamic_cast<NumberDescriptor *>(cond)->value.intValue;
        if (val == 1) {
            bodies()[i]->evaluate(symTab);
            done = true;
            break;
        } else if (val == 0) {
            continue;
        } else {
            std::cout << "IfStatement::evaluate The condition must evaluate to either 0 or 1\n";
            exit(1);
        }
    }
    if (!done && bodies().size() > size) { // if there's an else statement
        bodies()[i]->evaluate(symTab);
    }
}

std::vector<ExprNode*> &IfStatement::conditions() {
    return _conditions;
}

std::vector<Statements*> &IfStatement::bodies() {
    return _bodies;
}

void IfStatement::print() {
    std::cout << "if ";
    conditions()[0]->print();
    std::cout << ":" << std::endl;
    bodies()[0]->print();
    int i;
    int size = conditions().size();
    for (i = 1; i < size; i++) {
        std::cout << "elif ";
        conditions()[i]->print();
        std::cout << ":" << std::endl;
        bodies()[i]->print();
    }
    if (bodies().size() > size) { // if there's an else statement
        std::cout << "else:" << std::endl;
        bodies()[i]->print();
    }
}