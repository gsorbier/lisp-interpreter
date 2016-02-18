# Lisp interpreter in C++
A simple lisp interpreter in C++.

The lexer lives in main.cpp and reads a line from stdin into a vector<string> of tokens.

The parser lives in ast.cpp. The ast class takes the vector<string> output from the lexer as its constructor param and, after creation, contains a handle to the root of the resulting abstract syntax tree.
