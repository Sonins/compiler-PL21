#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iostream>
#include <list>
#include "Token.hpp"

class Scanner {
  private:
    static void pushFinateStateToken(std::list<Token>* tokens, char state, std::string tokenValue);
    static char goDfa(char state, char goTo);

  public:
    Scanner();
    ~Scanner();
    static std::list<Token> scan(std::list<char> sourceCode);
};

#endif