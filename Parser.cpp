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
    while (tok.eol())
        tok = tokenizer.getToken();
    while (tok.isName() || tok.isKeyword() || tok.isNewLineChar() || tok.isCommentChar()) {

        if (tok.getkeyword() == "print") {
            PrintStatement *printStmt = printStatement();
            stmts->addStatement(printStmt);
        }

       else if (tok.getkeyword() == "for"){
           ForStatement *forstmt = forStatement();
            stmts->addStatement(forstmt);
            tok = tokenizer.getToken();
            if (tok.isName())
                continue;
            else
                tokenizer.ungetToken();

        }

        else if (tok.getkeyword() == "if"){
            IfStatement *ifStmt = ifStatement();
            stmts->addStatement(ifStmt);
        }

        else if (tok.isName()){
            tokenizer.ungetToken();
            Statement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);

            tok = tokenizer.getToken();

        }
        else if (tok.isCmnt()) {
            tok = tokenizer.getToken();
            if (!tok.eol() && !tok.eof() && !tok.dedent())
                die("Parser::statements", "Expected an eol token, instead got", tok);
        }


        if (!tok.eof()) {
            tok = tokenizer.getToken();
            while (tok.eol())
                tok = tokenizer.getToken();
        }
    }
    while (tok.eol())
        tok = tokenizer.getToken();
    tokenizer.ungetToken();
    return stmts;
}



PrintStatement *Parser::printStatement() {
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

        Token endLine = tokenizer.getToken();
        if (!endLine.eol() && !endLine.eof() && !endLine.isCmnt() && !endLine.dedent())
            die("Parser::printStatement", "Expected an end of line token, instead got", endLine);
        if (endLine.eof() || endLine.isCmnt() || endLine.dedent())
            tokenizer.ungetToken();

        return new PrintStatement("Print", exprs);
}


Statement *Parser::assignStatement() {
    // Parses the following grammar rule
    //
    // <assign-stmtement> -> <id> = <expr>

    Token varName = tokenizer.getToken();
    if (!varName.isName() && !varName.eof()) {
            die("Parser::assignStatement", "Expected a name token or keyword, instead got", varName);

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

std::vector<ExprNode*> Parser::testlist() {
    // This function parses the grammar rule:

    // testlist: test {',' test}*

    std::vector<ExprNode*> list;
    list.push_back(test());
    Token tok = tokenizer.getToken();
    while (tok.symbol() == ',') {
        list.push_back(test());
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return list;
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
    if (tok.isName() || tok.getkeyword() == "i") {
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


ForStatement *Parser::forStatement() {
    // This function parses the grammar rule:

    // for_stmt: 'for' ID 'in' 'range' '(' testlist ')'  ':' suite

    Token loopVar = tokenizer.getToken();
    if (!loopVar.isName())
        die("Parser::forStatement", "Expected a name token, instead got", loopVar);

    Token t = tokenizer.getToken();

    if (t.getkeyword() != "in")
        die("Parser::forStatement", "Expected the 'in' keyword, instead got", t);

    t = tokenizer.getToken();
    if (t.getkeyword() != "range")
        die("Parser::forStatement", "Expected the 'range' keyword, instead got", t);

    t = tokenizer.getToken();
    if (!t.isOpenParen())
        die("Parser::forStatement", "Expected an open parenthesis, instead got", t);

    std::vector<ExprNode*> args = testlist();

    if (args.size() > 3) {
        Token empty;
        die("Parser::forStatement", "Expected a list of at most 3 integers, instead got more than 3 integers", empty);
    }

    t = tokenizer.getToken();
    if (!t.isCloseParen())
        die("Parser::forStatement", "Expected a close parenthesis, instead got", t);

    t = tokenizer.getToken();
    if (t.symbol() != ':')
        die("Parser::forStatement", "Expected a colon, instead got", t);

    t = tokenizer.getToken();
    if (t.isCmnt())
        t = tokenizer.getToken();
    if (t.eol())
        tokenizer.ungetToken();

    Statements *body = suite();

    return new ForStatement(loopVar, args, body);
}



Statements *Parser::suite() {
    // This function parses the grammar rule:

    // suite: NEWLINE INDENT stmt+ DEDENT

    Token t = tokenizer.getToken();
    if (t.isCmnt())
        t = tokenizer.getToken();
    if (!t.eol())
        die("Parser::suite", "Expected an end of line token, instead got", t);

    t = tokenizer.getToken();
    while (t.eol())
        t = tokenizer.getToken();
    if (!t.indent())
        die("Parser::suite", "Expected an indent token, instead got", t);

    Statements *stmts = statements();

    t = tokenizer.getToken();
    if (!t.dedent() && !t.eof())
        die("Parser::suite", "Expected a dedent token, instead got", t);

    return stmts;
}

IfStatement *Parser::ifStatement() {
    // This function parses the grammar rule:

    // if_stmt: ’if’ test ’:’ suite {’elif’ test ’:’ suite}* [’else’ ’:’ suite]

    std::vector<ExprNode*> conditions;
    conditions.push_back(test());

    Token t = tokenizer.getToken();
    if (t.symbol() != ':')
        die("Parser::ifStatement", "Expected a colon, instead got", t);

    std::vector<Statements*> bodies;
    bodies.push_back(suite());

    t = tokenizer.getToken();
    while (t.getkeyword() == "elif") {
        conditions.push_back(test());
        t = tokenizer.getToken();
        if (t.symbol() != ':')
            die("Parser::ifStatement", "Expected a colon, instead got", t);
        bodies.push_back(suite());
        t = tokenizer.getToken();
    }

    if (t.getkeyword() =="else") {
        t = tokenizer.getToken();
        if (t.symbol() != ':')
            die("Parser::ifStatement", "Expected a colon, instead got", t);
        bodies.push_back(suite());
    }
    else
        tokenizer.ungetToken();

    return new IfStatement(conditions, bodies);
}



