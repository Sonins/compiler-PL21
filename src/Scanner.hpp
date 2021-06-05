#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iostream>
#include <list>
#include "Token.hpp"

class Scanner {
  private:

  public:
    Scanner();
    ~Scanner();
    static std::list<Token*> scan(std::string sourceCode);
};

#endif