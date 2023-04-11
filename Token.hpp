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

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

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
    bool isEqualToOperator()  const {return _longSymbol == "==";}
    bool isGreaterThanEqualOperator() const {return _longSymbol == ">=";}
    bool isLessThanEqualOperator() const {return _longSymbol == "<=";}
    bool notEqualOperator() const {return _longSymbol == "!=";}
    bool isRelationalOperator() const {
            return isGreaterThanOperator() ||
                   isLessThanOperator() ||
                   isEqualToOperator () ||
                   isGreaterThanEqualOperator() ||
                   isLessThanEqualOperator() ||
                   notEqualOperator();
    }
    bool isName() const                   { return _name.length() > 0; }
    bool isKeyword() const { return _keyWord == "for" || _keyWord == "print";}
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    std::string getKeyWord() const {return _keyWord;}
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }

    void print() const;

private:
    std::string _name;
    bool _eof, _eol;
    bool _isWholeNumber;
    char _symbol;
    std::string _longSymbol;
    int _wholeNumber;
    std::string _keyWord;
};


#endif //APYTHONINTERPRETER_TOKEN_HPP
