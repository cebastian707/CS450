cmake_minimum_required(VERSION 3.23.2)
project(APythonInterpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(APythonInterpreter main.cpp Token.cpp Token.hpp Tokenizer.cpp Tokenizer.hpp Parser.cpp Parser.hpp ExprNode.cpp ExprNode.hpp SymTab.cpp SymTab.hpp Statements.cpp Statements.hpp TypeDescriptor.cpp TypeDescriptor.hpp Range.hpp Range.cpp)
