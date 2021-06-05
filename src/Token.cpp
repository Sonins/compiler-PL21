#include "Token.hpp"

Token::Token(TokenType type, std::string value) {
  Token::type = type;
  Token::value = value;
}

TokenType Token::getType() {
  return Token::type;
}