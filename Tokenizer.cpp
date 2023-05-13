//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);

    return name;
}

int Tokenizer::readInteger() {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    int intValue = 0;
    char c;
    while( inStream.get(c) && isdigit(c) ) {
        intValue = intValue * 10 + c - '0';
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return intValue;
}

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{}, parsingANewLine{true} {
    indentStack.push_back(0);
}


Token Tokenizer::getToken() {

    if(ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;
    int numSpaces = 0;

    while (inStream.get(c) && isspace(c) && c != '\n')
        numSpaces++;



    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }


    Token token;
    if( inStream.eof()) {
        if (indentStack.back() != 0) {
            token.dedent() = true;
            indentStack.pop_back();
            _tokens.push_back(token);
            return lastToken = token;
        }
        token.eof() = true;
        _tokens.push_back(token);
        return lastToken = token;
        token.eof() = true;
    }    if (parsingANewLine) {
        if (c == '\n') {
            token.eol() = true;
            parsingANewLine = true;
            _tokens.push_back(token);
            return lastToken = token;
        }
        if (numSpaces > indentStack.back()) {
            inStream.putback(c);
            token.indent() = true;
            indentStack.push_back(numSpaces);
            parsingANewLine = false;
            _tokens.push_back(token);
            return lastToken = token;
        } else if (numSpaces < indentStack.back()) {
            bool valid = false;
            for (int i = indentStack.size(); i >= 0; i--) {
                if (numSpaces == indentStack[i]) {
                    valid = true;
                    break;
                }
            }
            if (!valid) {
                std::cout << std::endl << "Tokenizer::getToken invalid indentation level" << std::endl;
                exit(1);
            }
            inStream.putback(c);
            token.dedent() = true;
            indentStack.pop_back();
            if (indentStack.back() == numSpaces)
                parsingANewLine = false;
            _tokens.push_back(token);
            return lastToken = token;
        }
    }
    parsingANewLine = false;
     if( c == '\n' ) {  // will not ever be the case unless new-line characters are not supressed.
        token.eol() = true;
        parsingANewLine = true;
        token.symbol('\n');
    }
     else if( isdigit(c) ) { // a integer?

         char d  = inStream.peek();
        if (d == '.'){
            inStream.get(d);
           std::string number_double;
           number_double +=  c;
            number_double += d;

            while (inStream.get(c)){
                if (isspace(c) || c == ',' || c == ')'){
                    inStream.putback(c);
                    break;
                }
                number_double+=c;
            }
            double number;
            number = stod(number_double);
            token.setdouble(number);
        }
         else{
            inStream.putback(c);
            token.setWholeNumber(readInteger());
        }
    }
    else if( c == '=' ) {

        char d = inStream.peek();
        if (d == '=') {
            inStream.get(d);
            token.relationalSymbol("==");
        } else {
            token.symbol(c);
        }
    } else if(c == '>'){
        char d = inStream.peek();
        if (d == '='){
            inStream.get(d);
            token.relationalSymbol(">=");
        }
        else{
            token.symbol(c);
        }
    }else if (c == ','){
        token.symbol(c);

     }

     else if (c == '"') {  // recognize strings
        std::string str;
        while (inStream.get(c) && c != '"') {
            str += c;

        }
        token.setString(str);
    }
    else if (c == '<'){
        char hola = inStream.peek();
        if (hola == '='){
            inStream.get(hola);
            token.relationalSymbol("<=");
        }
        else{
            token.symbol(c);
        }

    } else if(c == '!'){
        char como = inStream.peek();
        if (como == '='){
            inStream.get(como);
            token.relationalSymbol("!=");
        } else{
            token.symbol(c);
        }
    }
    else if ( c == '/'){
        char estas = inStream.peek();
        if (estas == '/'){
            inStream.get(estas);
            token.relationalSymbol("//");
        } else{
            token.symbol(c);
        }
    }else if (c == '#') {
         std::string cmnt = "#";
         while (inStream.get(c) && c != '\n')
             cmnt += c;
         token.setCmnt(cmnt);
         token.symbol('#');
         inStream.putback(c);
     } else if (c == '-'){
        char d = inStream.peek();

        if (isdigit(d)){
            inStream.get(d);
            std::string number_double;
            number_double +=  c;
            number_double += d;

            while (inStream.get(c)){
                if (isspace(c) || c == ',' || c == ')'|| c == '\n'){
                    inStream.putback(c);
                    break;
                }
                number_double+=c;
            }
            int  number;
            number = std::stoi(number_double);
            token.setWholeNumber(number);
        } else{
            token.symbol('-');
        }
    }
    else if( c == '+'  || c == '*' || c == '%') {
        token.symbol(c);
    }

    else if( c == ';' || c == ':' ) {
        token.symbol(c);
    }

    else if( c == '(' || c == ')' || c == '{' || c == '}') {
       // std::cout<<"Curly brace check??: "<< c <<std::endl;
        token.symbol(c);
    }

    else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        std::string name = readName();
        if (name == "print" || name == "for" || name == "else" || name == "range" || name == "in"  || name == "and" || name == "not" || name == "or" || name == "if" || name == "elif"){
            token.setkeyword(name);
        }
        else{
            token.setName(name);
        }
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
   // token.print();
    _tokens.push_back(token);
    return lastToken = token;
}


void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        //std::cout << std::endl;
    }
}
