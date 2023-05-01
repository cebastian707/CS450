//
// Created by Ali Kooshesh on 4/4/23.
//


#include<iostream>
#include "ExprNode.hpp"

// ExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

TypeDescriptor *ExprNode::evaluate(SymTab &symTab) {
    return nullptr;
}

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

TypeDescriptor* InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    TypeDescriptor* leftValue = left()->evaluate(symTab);
    TypeDescriptor* rightValue = right()->evaluate(symTab);
    int result = 0;
    double  answer = 0;

    if( token().isAdditionOperator() ) {
        if (leftValue->type() == TypeDescriptor::INTEGER && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue + dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }
        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::INTEGER){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue + dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;

        }
        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue + dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }

        else {
            result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue + dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
        }
    }else if(token().isSubtractionOperator()) {
        if (leftValue->type() == TypeDescriptor::INTEGER && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue - dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }
        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::INTEGER){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue - dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;

        }
        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue - dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }

        else {
            result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue - dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
        }
    }else if(token().isMultiplicationOperator()) {
        if (leftValue->type() == TypeDescriptor::INTEGER && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue * dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }
        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::INTEGER){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue * dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;

        }
        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue * dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }

        else {
            result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue * dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
        }
    }else if(token().isDivisionOperator() || token()._isfloordivision()) {
        if (leftValue->type() == TypeDescriptor::INTEGER && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue / dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }

        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::INTEGER){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue / dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;

        }

        else if(leftValue->type() == TypeDescriptor::DOUBLE && rightValue->type() == TypeDescriptor::DOUBLE){
            answer = dynamic_cast<NumberDescriptor *>(leftValue)->value.doubleValue / dynamic_cast<NumberDescriptor *>(rightValue)->value.doubleValue;
            TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
            dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = answer;
            return desc;
        }

        else {
            result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue / dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
        }
    }else if( token().isModuloOperator() ) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue % dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }else if(token().isLessThanOperator()) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue < dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }else if (token().isLessThanEqualOperator()) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue <= dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }else if(token().isGreaterThanOperator()) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue > dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }else if (token().isGreaterThanEqualOperator()) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue >= dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }else if (token().isEqualToOperator()) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue == dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }else if(token().notEqualOperator()) {
        result = dynamic_cast<NumberDescriptor *>(leftValue)->value.intValue != dynamic_cast<NumberDescriptor *>(rightValue)->value.intValue;
    }
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
    TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::INTEGER);
    dynamic_cast<NumberDescriptor*>(desc)->value.intValue = result;
    return desc;
}

void InfixExprNode::print() {
    _left->print();
    token().print();
    _right->print();
}

// WHoleNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    token().print();
}


TypeDescriptor* StringLiteral::evaluate(SymTab& symTab) {
    std::string strValue = this->token().getstring();
    TypeDescriptor* desc = new StringDescriptor(TypeDescriptor::STRING);
    dynamic_cast<StringDescriptor*>(desc)->str = strValue;
    //symTab.setValueFor(token().getName(), desc);
    return desc;
}

TypeDescriptor* WholeNumber::evaluate(SymTab &symTab) {
    int intValue = token().getWholeNumber();
    if (debug)
        std::cout << "WholeNumber::evaluate: returning " << intValue << std::endl;
    TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::INTEGER);
    dynamic_cast<NumberDescriptor*>(desc)->value.intValue = intValue;
    
    return desc;
}


// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}


TypeDescriptor* Variable::evaluate(SymTab &symTab) {
    if (!symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }

    TypeDescriptor* desc = symTab.getValueFor(token().getName());

    if (desc == nullptr) {
        std::cout << "Variable::evaluate: Value for variable " << token().getName() << " is null" << std::endl;
        exit(1);
    }
    if (desc->type() == TypeDescriptor::INTEGER) {
        //std::cout << dynamic_cast<NumberDescriptor*>(desc)->value.intValue << " " << std::endl;
    } else if (desc->type() == TypeDescriptor::STRING) {
        //std::cout << dynamic_cast<StringDescriptor*>(desc)->str <<  " " <<  std::endl;
    }

    return desc;
}


StringLiteral::StringLiteral(Token token) : ExprNode(token) {

}

void StringLiteral::print() {
    token().print();
}


DoubleNumber::DoubleNumber(Token token) : ExprNode(token) {

}

TypeDescriptor *DoubleNumber::evaluate(SymTab &symTab) {
    double intValue = token().getdoubleNumber();
    if (debug)
        std::cout << "WholeNumber::evaluate: returning " << intValue << std::endl;
    TypeDescriptor* desc = new NumberDescriptor(TypeDescriptor::DOUBLE);
    dynamic_cast<NumberDescriptor*>(desc)->value.doubleValue = intValue;

    return desc;
}

void DoubleNumber::print() {
    token().print();
}
