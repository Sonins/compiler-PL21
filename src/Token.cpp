#include "Token.hpp"

Token::Token(TokenType type, std::string value) {
  Token::type = type;
  Token::value = value;
}

Token::~Token() {

}

TokenType Token::getType() {
  return Token::type;
}

std::string Token::getValue() {
  return Token::value;
}
