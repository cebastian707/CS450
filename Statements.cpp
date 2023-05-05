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
