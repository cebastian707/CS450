//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_TOKEN_HPP
#define APYTHONINTERPRETER_TOKEN_HPP

#include<string>

class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }
    bool isOpenCurly() const { return _symbol == '{'; }
    bool isCloseCurly() const { return _symbol == '}'; }

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }


    void relationalSymbol(std::string str) {_relationalSymbol = str;}
    std::string relationalSymbol() {return _relationalSymbol;}

    bool isCommentChar() const { return _symbol == '#'; }
    bool isNewLineChar() const {return _symbol == '\n'; }
    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator();
    }
    bool isGreaterThanOperator() const {return _symbol == '>';}
    bool isLessThanOperator() const {return _symbol == '<';}

    bool isEqualToOperator()  const {return _relationalSymbol == "==";}
    bool isGreaterThanEqualOperator() const {return _relationalSymbol == ">=";}
    bool isLessThanEqualOperator() const {return _relationalSymbol == "<=";}
    bool notEqualOperator() const {return _relationalSymbol == "!=";}

    bool isRelationalOperator() const {
            return isGreaterThanOperator() ||
                   isLessThanOperator() ||
                   isEqualToOperator () ||
                   isGreaterThanEqualOperator() ||
                   isLessThanEqualOperator() ||
                   notEqualOperator();
    }
    bool isName() const                   { return _name.length() > 0; }
    bool &isKeyword() { return _iskeyWord;}
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }
    bool strings(){return _istring;}
    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    std::string getkeyword(){return _keyword;}
    void setkeyword(std::string key){
        _keyword = key;
        isKeyword() = true;
    }
    void setString(const std::string& str) {
        _string = str;
        _istring = true;
    }

    std::string getstring(){
        return _string;
    }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }

    void print() const;


private:
    std::string _name;
    bool _eof, _eol;
    bool _isWholeNumber;
    bool _istring;
    char _symbol;
    std::string _relationalSymbol;
    int _wholeNumber;
    bool _iskeyWord = false;
    std::string _keyword;
    std::string _string;
};


#endif //APYTHONINTERPRETER_TOKEN_HPP
