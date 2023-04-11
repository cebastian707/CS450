cmake_minimum_required(VERSION 3.23)
project(python)

set(CMAKE_CXX_STANDARD 20)

add_executable(python main.cpp Token.cpp ArithExpr.cpp Parser.cpp Statments.cpp SymTab.cpp Tokenizer.cpp)
