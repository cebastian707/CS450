//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_TOKENIZER_HPP
#define APYTHONINTERPRETER_TOKENIZER_HPP


#include <fstream>
#include <vector>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::ifstream &inStream);
    Token getToken();
    void ungetToken();
    void printProcessedTokens();

private:
    Token lastToken;
    bool ungottenToken;
    std::ifstream &inStream;
    std::vector<Token> _tokens;

private:
    std::string readName();
    int readInteger();
};

#endif //APYTHONINTERPRETER_TOKENIZER_HPP
