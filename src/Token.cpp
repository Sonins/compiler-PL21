#include "Token.hpp"

Token::Token(TokenType type, std::string value) {
  Token::type = type;
  Token::value = value;
}

Token::~Token() {

}

std::string Token::getTokenTypeName() {
  if (Token::type == TOKEN_TYPE_WORD) return "WORD";
  if (Token::type == TOKEN_TYPE_NUMBER) return "NUMBER";
  if (Token::type == TOKEN_TYPE_LPAREN) return "LPAREN";
  if (Token::type == TOKEN_TYPE_RPAREN) return "RPAREN";
  if (Token::type == TOKEN_TYPE_LBRACE) return "LBRACE";
  if (Token::type == TOKEN_TYPE_RBRACE) return "RBRACE";
  if (Token::type == TOKEN_TYPE_INT) return "INT";
  if (Token::type == TOKEN_TYPE_CHAR) return "CHAR";
  if (Token::type == TOKEN_TYPE_ASSIGN) return "ASSIGN";
  if (Token::type == TOKEN_TYPE_PLUS) return "PLUS";
  if (Token::type == TOKEN_TYPE_IF) return "IF";
  if (Token::type == TOKEN_TYPE_ELSE) return "ELSE";
  if (Token::type == TOKEN_TYPE_THEN) return "THEN";
  if (Token::type == TOKEN_TYPE_SEMICOLON) return "SEMICOLON";
  if (Token::type == TOKEN_TYPE_LESS_THEN) return "LESS_THEN";
  return "";
}

TokenType Token::getType() {
  return Token::type;
}

std::string Token::getValue() {
  return Token::value;
}
