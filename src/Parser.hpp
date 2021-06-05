#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <list>
#include "Token.hpp"
#include "SyntaxTree.hpp"

class Parser {
  private:

  public:
    Parser();
    ~Parser();
    static SyntaxTree* parse(std::list<Token*> tokens);
};

#endif