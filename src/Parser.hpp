#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <list>
#include "ParsingTable.hpp"
#include "Token.hpp"
#include "SyntaxTree.hpp"

class Parser {
  private:
    parsing_table table;
  public:
    Parser();
    ~Parser();
    void print_parsing_table();
    static SyntaxTree* parse(std::list<Token> tokens);
};

#endif