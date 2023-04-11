/*
Complier/Interpreter structure/architecutre
    -comp/inte use context-free grammar to validate programs
    -context-free grammer is a set of rules discribing the syntax of a program
     
A parser recieves tokens and uses the rules of its CFG to interpert the tokens
The parser builds an Abstract Syntax Tree, which represents the code of the program

//tokens: int/main/open parens/int/argc/,/char/asterisk/open bracket/close bracket/close parens
int main(int argc, char * argv[]){


}
    

regex example: variable names [a-zA-Z_][a-zA-Z0-9_]* in other words, a variable has to start with a letter or unnderscore
followed by any of the characters in the second set of brackets


Abstraxt Syntax Tree: 
a = 20 + 5
b = a * 6

|ASSINGMENT STATEMENT|
  
  a          +
            / \
           20  5


keywords examples: int/main

symbol table: a map of the variables in the AST
so for a = 20 + 5, it assigns the value 25 to a

grammar rule!
int a = 10;
<statements> -> <statement>{<statement>}

<id> -> [a-zA-Z][_a-zA-Z0-9]*


*/