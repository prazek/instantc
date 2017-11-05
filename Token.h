#pragma once
#include <string>

enum class TokenType {
  // Used only internally
  SPACE = -1,

  // Used outside
  OPERATOR,
  ID,
  NUM,
  SEMI,
  END_FILE,
  INVALID
};


struct Token {
  TokenType type;
  std::string string;
};