//
// Created by Ali Kooshesh on 4/4/23.
//


#include<vector>
#include<iostream>
#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions
void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    // This function is called when we KNOW that we are about to parse
    // a series of assignment statements.

    // This function parses the grammar rules:

    // <statement> -> <assignStatement> <statement>
    // <statement> -> Epsilon


    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName() || tok.isKeyword() || tok.isNewLineChar()) {
        if (tok.isNewLineChar()){
             tok = tokenizer.getToken();
             //std::cout << "Skipping newline char"<<std::endl;
             continue;
        }
        if (tok.getkeyword() == "for"){
            Statement *stmt = forstatement();
            stmts->addStatement(stmt);
            tok = tokenizer.getToken();
            while (tok.symbol() == '\n'||tok.symbol() == '}'){
                tok = tokenizer.getToken();
            }

            if (tok.eof()){
                break;
            }

        }


        tokenizer.ungetToken();
        Statement *assignStmt = assignStatement();
        stmts->addStatement(assignStmt);


       
        tok = tokenizer.getToken();
        while (tok.symbol() == '\n'){
            tok = tokenizer.getToken();
        }

    }
    tokenizer.ungetToken();
    return stmts;
}

Statement *Parser::assignStatement() {
    // Parses the following grammar rule
    //
    // <assign-stmtement> -> <id> = <expr>

    Token varName = tokenizer.getToken();
    if (!varName.isName() && !varName.eof()) {
        // If the token is a keyword, parse a print statement instead
        if (varName.isKeyword() && varName.getkeyword() == "print") {
            std::vector<ExprNode*> exprs = testlist();
            Token close = tokenizer.getToken();
            if (close.symbol() != '\n') {
                die("Parser::assignStatement", "Expected an end of line token", close);
            }
            return new PrintStatement(varName.getkeyword(), exprs);
        }

        else {
            die("Parser::assignStatement", "Expected a name token or keyword, instead got", varName);
        }
    }

    Token assignOp = tokenizer.getToken();

    if (!assignOp.isAssignmentOperator() && !varName.eof()) {
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);
    }

    //rel experssion is -> test
    ExprNode *rightHandSideExpr = test();


    return new AssignmentStatement(varName.getName(), rightHandSideExpr);
}

ExprNode* Parser::term() {
    // This function parses the grammar rule:
    // <term> -> <factor> {(MULT | DIV | MOD | FLOORDIV) <factor>}
    ExprNode* left = factor();
    Token tok = tokenizer.getToken();
    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator() || tok._isfloordivision()) {
        InfixExprNode* p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = factor();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode* Parser::arith_expr() {
    // This function parses the grammar rule:
    // <arith_expr> -> <term> {('+' | '-') <term>}
    ExprNode* left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) {
        InfixExprNode* p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode* Parser::test() {
    // This function parses the grammar rule:
    // <test> -> <or_test>
    return or_test();
}

ExprNode* Parser::factor() {
    // This function parses the grammar rule:
    // <factor> -> {'-'} <factor> | <atom>

    Token tok = tokenizer.getToken();
    if (tok.isSubtractionOperator()) {
        InfixExprNode* p = new InfixExprNode(tok);
        p->right() = factor();
        return p;
    }
    tokenizer.ungetToken();
    return atoms();
}

ExprNode *Parser::print() {
    //Token tok = tokenizer.getToken();
    ExprNode* p = test();
    return p;
}

Statement* Parser::forstatement() {
    std::cout << "About to parse for loop"<<std::endl;
    std::cout << "Key word  for has beened parsed"<<std::endl;

    Token tok = tokenizer.getToken();

    tokenizer.ungetToken();

    //get the variable name
    ExprNode* variable = test();


    //look for the key word in
    tok = tokenizer.getToken();

    //if not key word in exit out
    if (tok.getkeyword() != "in"){
        die("Parser::forstatement", "Execpeted keyword in", tok);
        exit(1);
    }

    //look for the keyword range
    tok = tokenizer.getToken();

    if (tok.getkeyword() != "range"){
        die("Parser::forstatement", "Execpeted keyword range", tok);
        exit(1);
    }

    //look for the open ( parenthesis
    tok = tokenizer.getToken();

    if (tok.symbol() != '('){
        die("Parser::forstatement", "Execpeted (", tok);
        exit(1);
    }

    //start parsing the range we need digits
    std::vector<ExprNode*> nums;
    ExprNode *start = test();
    nums.push_back(start);


    //start looking for the second number or look for a )
    tok = tokenizer.getToken();

    if (tok.symbol() == ','){
        start = test();

        nums.push_back(start);

        tok = tokenizer.getToken();

        if (tok.symbol() == ','){
            start = test();
            nums.push_back(start);
            tok = tokenizer.getToken();
        }

    }


    if (tok.symbol() != ')'){
        die("Parser::forstatement", "Execpeted )", tok);
        exit(1);
    }

    //look for the :
    tok = tokenizer.getToken();

    if (tok.symbol() != ':'){
        die("Parser::forstatement", "Execpeted :", tok);
        exit(1);
    }


    tok = tokenizer.getToken();

    if (tok.symbol() != '\n'){
        die("Parser::forstatement", "Execpeted newline", tok);
        exit(1);
    }

    //parse the body of the for loop
    Statements* body = statements();


    ForStatement* forStmt = new ForStatement(variable,nums,body);

    return forStmt;
}

std::vector<ExprNode*> Parser::testlist() {
    std::vector<ExprNode*> exprs;
    Token tok = tokenizer.getToken();

    // Check if the testlist starts with a left parenthesis
    if (tok.symbol() != '('){
        die("Parser::testlist", "Expected open-parenthesis, instead got", tok);
    }

    tok = tokenizer.getToken();
    ExprNode *expr;

    while (tok.symbol() != ')'){
        if (tok.strings()){
            tokenizer.ungetToken();
            expr = atoms();
            exprs.push_back(expr);
            tok = tokenizer.getToken();
        }
        if (tok.symbol() ==  ')'){
            break;
        }

        while (tok.symbol() == ','){
            tok = tokenizer.getToken();
        }

         if (!tok.strings()){
            tokenizer.ungetToken();
            expr = test();
            exprs.push_back(expr);
            tok = tokenizer.getToken();
        }
        while (tok.symbol() == ','){
            tok = tokenizer.getToken();
        }
        if (tok.symbol() ==  ')'){
            break;
        }
    }

    return exprs;
}

ExprNode *Parser::or_test() {
    // This function parses the grammar rules:

    // <or_test> -> <and_test> {'or' <and_test>}
    // <and_test> -> <not_test> {'and' <not_test>}
    // <not_test> -> 'not' <not_test> | <comparison>
    // <comparison> -> <arith_expr> {(==, !=, <, <=, >, >=) <arith_expr>}

    ExprNode *left = and_test();
    Token tok = tokenizer.getToken();

    while (tok.getkeyword() == "or") {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = and_test();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::and_test() {
    // This function parses the grammar rule:
    // <and_test> -> <not_test> {and <not_test>}
    ExprNode *left = not_test();
    Token tok = tokenizer.getToken();
    while (tok.getkeyword() == "and") {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = not_test();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::not_test() {
    // This function parses the grammar rule:
    // <not_test> -> not <not_test> | <comparison>
    Token tok = tokenizer.getToken();
    if (tok.getkeyword() == "not") {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = not_test();
        return p;
    }
    tokenizer.ungetToken();
    return comparison();
}

ExprNode* Parser::comparison() {
    // This function parses the grammar rule:
    // <comparison> -> <expr> {<comp_op> <expr>}
    ExprNode* left = arith_expr();
    Token tok = tokenizer.getToken();
    while (tok.isEqualToOperator() || tok.notEqualOperator() || tok.isGreaterThanOperator() || tok.isGreaterThanEqualOperator() || tok.isLessThanOperator() || tok.isLessThanEqualOperator()) {
        InfixExprNode* p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = arith_expr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode* Parser::atoms() {
    // This function parses the grammar rule:
    // <atom> -> ID | NUMBER | STRING+ | '(' <expr> ')'
    Token tok = tokenizer.getToken();
    if (tok.isName()) {
        return new Variable(tok);
    } else if (tok.isWholeNumber()) {
        return new WholeNumber(tok);
    } else if (tok.isdecimal()) {
        return new DoubleNumber(tok);
    } else if (tok.strings()) {
        return new StringLiteral(tok);
    } else if (tok.isOpenParen()) {
        ExprNode* p = test();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen()) {
            die("Parser::atom", "Expected close-parenthesis, instead got", token);
        }
        return p;
    } else {
        die("Parser::atom", "Unexpected token", tok);
        return nullptr;  // unreachable, but quiets the warning
    }
}








