#include "Scanner.hpp"

std::list<Token> Scanner::scan(std::list<char> sourceCode) {
  std::list<Token> tokens;
  char state = 0;
  std::string tokenValue = "";

  for(std::list<char>::iterator iter = sourceCode.begin(); iter != sourceCode.end(); iter++){
    if (*iter == '(') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_LPAREN, "("));
    } else if (*iter == ')') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_RPAREN, ")"));
    } else if (*iter == '{') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_LBRACE, "{"));
    } else if (*iter == '}') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_RBRACE, "}"));
    } else if (*iter == ';') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_SEMICOLON, ";"));
    } else if (*iter == '=') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_ASSIGN, "="));
    } else if (*iter == '+') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_PLUS, "+"));
    } else if (*iter == '<') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
      tokens.push_back(Token(TOKEN_TYPE_LESS_THEN, "<"));
    } else if (*iter == ' ' || *iter == '\n' || *iter == '\t') {
      Scanner::pushFinateStateToken(&tokens, state, tokenValue);
      state = 0;
      tokenValue = "";
    } else {
      tokenValue.push_back(*iter);
      state = Scanner::goDfa(state, *iter);
    }
  }
  std::cout << std::endl;
  return tokens;
}

void Scanner::pushFinateStateToken(std::list<Token>* tokens, char state, std::string tokenValue) {
  if (state == 6) {
    tokens->push_back(Token(TOKEN_TYPE_IF, tokenValue));
  } else if (state == 11) {
    tokens->push_back(Token(TOKEN_TYPE_INT, tokenValue));
  } else if (state == 15) {
    tokens->push_back(Token(TOKEN_TYPE_CHAR, tokenValue));
  } else if (state == 16) {
    tokens->push_back(Token(TOKEN_TYPE_THEN, tokenValue));
  } else if (state == 17) {
    tokens->push_back(Token(TOKEN_TYPE_ELSE, tokenValue));
  } else if (state == 18) {
    tokens->push_back(Token(TOKEN_TYPE_NUMBER, tokenValue));
  } else if (state != 0) {
    tokens->push_back(Token(TOKEN_TYPE_WORD, tokenValue));
  }
}

char Scanner::goDfa(char state, char goTo) {
  if (state == 0) {
    if (goTo == 'i') {
      return 1;
    } else if (goTo == 'c') {
      return 2;
    } else if (goTo == 't') {
      return 3;
    } else if (goTo == 'e') {
      return 4;
    } else if (goTo >= '0' && goTo <= '9') {
      return 18;
    } else {
      return 5;
    }
  } else if (state == 1) {
    if (goTo == 'f') {
      return 6;
    } else if (goTo == 'n') {
      return 7;
    } else {
      return 5;
    }
  } else if (state == 2) {
    if (goTo == 'h') {
      return 8;
    } else {
      return 5;
    }
  } else if (state == 3) {
    if (goTo == 'h') {
      return 9;
    } else {
      return 5;
    }
  } else if (state == 4) {
    if (goTo == 'l') {
      return 10;
    } else {
      return 5;
    }
  } else if (state == 5) {
    return 5;
  } else if (state == 6) {
    return 5;
  } else if (state == 7) {
    if (goTo == 't') {
      return 11;
    } else {
      return 5;
    }
  } else if (state == 8) {
    if (goTo == 'a') {
      return 12;
    } else {
      return 5;
    }
  } else if (state == 9) {
    if (goTo == 'e') {
      return 13;
    } else {
      return 5;
    }
  } else if (state == 10) {
    if (goTo == 's') {
      return 14;
    } else {
      return 5;
    }
  } else if (state == 11) {
    return 5;
  } else if (state == 12) {
    if (goTo == 'r') {
      return 15;
    } else {
      return 5;
    }
  } else if (state == 13) {
    if (goTo == 'n') {
      return 16;
    } else {
      return 5;
    }
  } else if (state == 14) {
    if (goTo == 'e') {
      return 17;
    } else {
      return 5;
    }
  } else if (state == 15) {
    return 5;
  } else if (state == 16) {
    return 5;
  } else if (state == 17) {
    return 5;
  } else if (state == 18) {
    if (goTo >= '0' && goTo <= '9') {
      return 18;
    } else {
      return 5;
    }
  }
  return 0;
}
