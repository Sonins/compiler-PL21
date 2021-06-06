#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

enum TokenType {
  TOKEN_TYPE_WORD,           // 0: string
  TOKEN_TYPE_NUMBER,         // 1: 0 ~ 9
  TOKEN_TYPE_IF,             // 2: if
  TOKEN_TYPE_THEN,           // 3: then
  TOKEN_TYPE_ELSE,           // 4: else
  TOKEN_TYPE_ASSIGN,         // 5: =
  TOKEN_TYPE_PLUS,           // 6: +
  TOKEN_TYPE_LESS_THEN,      // 7: <
  TOKEN_TYPE_SEMICOLON,      // 8: ;
  TOKEN_TYPE_LPAREN,         // 9: (
  TOKEN_TYPE_RPAREN,         // 10: )
  TOKEN_TYPE_LBRACE,         // 11: {
  TOKEN_TYPE_RBRACE,         // 12: }
  TOKEN_TYPE_EXIT,           // 13: exit
  TOKEN_TYPE_INT,            // 14: int
  TOKEN_TYPE_CHAR,           // 15: char
};

class Token {
  private:
    TokenType type;
    std::string value;

  public:
    Token(TokenType type, std::string value);
    ~Token();
    std::string getTokenTypeName();
    TokenType getType();
    std::string getValue();
};

#endif