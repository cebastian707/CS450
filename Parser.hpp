//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_PARSER_HPP
#define APYTHONINTERPRETER_PARSER_HPP

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "SymTab.hpp"
#include "ExprNode.hpp"
#include "Statements.hpp"

#include<vector>
#include<iostream>
#include<map>


class Parser {
public:
    Parser(Tokenizer &tokenizer) : tokenizer{tokenizer} {}
    Statements *statements();
    Statement *assignStatement();
    Statement *print_quick(std::string keys);
    ExprNode *print();
    Statement * forstatement();
    //ExprNode *expr();
    //ExprNode *term();
    //ExprNode *primary();
    //std::string id();

private:
    Tokenizer &tokenizer;

    void die(std::string where, std::string message, Token &token);

    std::vector<ExprNode *> testlist();

    ExprNode *comparison();

    ExprNode *not_test();

    ExprNode *and_test();

    ExprNode *or_test();

    ExprNode *test();

    ExprNode *arith_expr();

    ExprNode *factor();

    ExprNode *atoms();


    ExprNode *term();
};


#endif //APYTHONINTERPRETER_PARSER_HPP
