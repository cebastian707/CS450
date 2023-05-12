//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include "Token.hpp"

Token::Token(): _name{""}, _eof{false}, _eol{false}, _symbol{'\0'}, _relationalSymbol ("\0"), _isWholeNumber{false} {}

void Token::print() const {
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if ( isOpenCurly() ) std::cout << "{";
    else if ( isCloseCurly() ) std::cout << "}";
    else if( isAssignmentOperator() )  std::cout << " = " ;
    else if( isSemiColon() )  std::cout << ";" ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isGreaterThanOperator() ) std::cout << " > ";
    else if( isLessThanOperator() )  std::cout << " < ";
    else if( isEqualToOperator() ) std::cout << " == ";
    else if( isGreaterThanEqualOperator() ) std::cout << " >= ";
    else if( isLessThanEqualOperator() ) std::cout << " <= ";
    else if( notEqualOperator() ) std::cout << " != ";
    else if( isName() )  std::cout << getName();
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else if (_iskeyWord ) std::cout << _keyword;
    else if (_istring)std::cout<<_string;
    else if ( isNewLineChar() ) std::cout << "\n";
    else if ( isCommentChar() ) std::cout<< '#';
    else if(_double_dl){std::cout << _double;}
    else if(isIndent()) std::cout << "Indent";
    else if(isDedent())std::cout<<"Dedent";
    
    else std::cout << "Uninitialized token: " << _symbol << std::endl;
}
