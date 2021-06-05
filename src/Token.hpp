#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

enum TokenType {
  WORD,           // string
  NUMBER,         // 0 ~ 9
  IF,             // if
  THEN,           // then
  ELSE,           // else
  ASSIGN,         // =
  PLUS,           // +
  LESS_THEN,      // <
  SEMICOLON,      // ;
  LPAREN,         // (
  RPAREN,         // )
  LBRACE,         // {
  RBRACE,         // }
  EXIT,           // exit
};

class Token {
  private:
    TokenType type;
    std::string value;

  public:
    Token(TokenType type, std::string value);
    ~Token();
    TokenType getType();
    std::string getValue();
};

#endif