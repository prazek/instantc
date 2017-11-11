#pragma once
#include <string>
#include <tuple>
#include <iostream>

enum class TokenType {
  // Used only internally
  SPACE = -1,

  // Used outside
  OPERATOR,
  ASSIGN,
  ID,
  NUM,
  SEMI,
  END_FILE,
  INVALID
};

inline std::ostream &operator<<(std::ostream &os, TokenType type) {
  return os << (int)type;
}


struct Token {
  TokenType type;
  std::string string;

  bool operator==(const Token &other) const {
    return std::tie(type, string) == std::tie(other.type, other.string);
  }
  friend std::ostream &operator<<(std::ostream& os, const Token &token) {
    return os << token.type << " " << token.string;
  }
};