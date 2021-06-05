#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <iostream>
#include "SyntaxTree.hpp"

class CodeGenerator {
  private:

  public:
    CodeGenerator();
    ~CodeGenerator();
    static std::string generate(SyntaxTree* syntaxTree);
};

#endif