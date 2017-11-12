#pragma once

#include <fstream>
#include <assert.h>
#include "Token.h"
class Lexer {
public:
  Lexer(std::istream &ifs) : ifs_(ifs) {
    lastToken_ = getNextToken();
  }

  const Token& currentToken() const {
    return lastToken_;
  }

  const Token &nextToken() {
    if (lastToken_.type == TokenType::END_FILE)
      assert(false && "Can't go through the end");
    lastToken_ = getNextToken();
    return lastToken_;
  }

private:
  Token getNextToken() {
    while (std::isspace(ifs_.peek())) {
      ifs_.get();
      lastToken_.type = TokenType::SPACE;
    }

    char current = ifs_.peek();
    if (current == EOF)
      return getEOF();
    if (std::isalpha(current))
      return getID(current);

    if (std::isdigit(current))
      return getNumber(current);

    switch (current) {
    case ';':
      return Token{TokenType::SEMI, std::string(1, char(ifs_.get()))};
    case '=':
      return Token{TokenType::ASSIGN, std::string(1, char(ifs_.get()))};
    case '+':
    case '*':
    case '-':
    case '/':
      return getOperator();

    case '(':
      return Token{TokenType::OPEN_PAREN, std::string(1, char(ifs_.get()))};
    case ')':
      return Token{TokenType::CLOSE_PAREN, std::string(1, char(ifs_.get()))};
    default:
      assert(false);
    }

  }
  Token getOperator() const {
    char op = ifs_.get();
    return Token{TokenType::OPERATOR, std::string(1, op)};
  }

  Token getNumber(char current) const {
    std::string num;

    while (isdigit(current)) {
        num.push_back(ifs_.get());
        current = ifs_.peek();
      }
    if (isalpha(current))
        return getInvalid(num);

    return Token{TokenType::NUM, move(num)};
  }

  Token getID(char current) const {
    assert(lastToken_.type != TokenType::ID);
    std::string id;

    while (isalpha(current) || isdigit(current)) {
        id.push_back(ifs_.get());
        current = ifs_.peek();
      }

    return Token{TokenType::ID, move(id)};
  }

  Token getInvalid(std::string s = "") const {
    return Token{TokenType::INVALID, std::move(s)};
  }
  Token getEOF() const {
    return Token{TokenType::END_FILE, {}};
  }
private:
  std::istream &ifs_;
  Token lastToken_;

};

