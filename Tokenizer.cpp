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

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{} {}



Token Tokenizer::getToken() {

    if(ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;
    /*
    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars.
        ;
    */


    while( inStream.get(c) && (isspace(c) || c == '#') && c != '\n'){  // Skip spaces including the new-line chars.
        if (c == '#'){
            while (inStream.get(c) && c!= '\n')
                ;
         
        }
    }

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }


    //std::cout << "c = " << c << std::endl;

    Token token;
    if( inStream.eof()) {
        token.eof() = true;
    } else if( c == '\n' ) {  // will not ever be the case unless new-line characters are not supressed.
        //token.eol() = true;
        token.symbol(c);
    }
     else if( isdigit(c) ) { // a integer?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        token.setWholeNumber( readInteger() );

    }else if (c == '#') {
        while (inStream.get(c) && c != '\n');
        return getToken();
    }else if( c == '=' ) {
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
    }else if (c == '"') {  // recognize strings
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

    else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        token.symbol(c);
    }

    else if( c == ';' ) {
        token.symbol(c);
    }

    else if( c == '(' || c == ')' || c == '{' || c == '}') {
        token.symbol(c);
    }

    else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        std::string name = readName();
        if (name == "print" || name == "for"){
            token.setkeyword(name);
        }
        else{
            token.setName(name);
        }
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
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
