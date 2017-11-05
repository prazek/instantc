
#include "gtest/gtest.h"
#include "Lexer.h"
#include <sstream>

namespace {

TEST(LexerTest, Empty) {
  const std::string empty = "";

  std::istringstream iss{empty};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, One) {
  const std::string one = "1";

  std::istringstream iss{one};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::NUM, one}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, Number) {
  const std::string number = "1234567890";

  std::istringstream iss{number};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::NUM, number}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, SimpleId) {
  const std::string a = "a";

  std::istringstream iss{a};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::ID, a}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, Id) {
  const std::string id = "abcd123a";

  std::istringstream iss{id};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::ID, id}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, Invalid1) {
  const std::string invalid1 = "2abc";

  std::istringstream iss{invalid1};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::INVALID, "2"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::ID, "abc"}));

  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, Invalid2) {
  const std::string invalid2 = "1 2"; // *valid for the lexer.

  std::istringstream iss{invalid2};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::NUM, "1"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "2"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}

TEST(LexerTest, Simple) {
  const std::string simple = "1 + 2;3*4/-=";

  std::istringstream iss{simple};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::NUM, "1"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::OPERATOR, "+"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "2"}));

  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::SEMI, ";"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "3"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::OPERATOR, "*"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "4"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::OPERATOR, "/"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::OPERATOR, "-"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::ASSIGN, "="}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::END_FILE, ""}));
}
TEST(LexerTest, Simple2) {
  const std::string simple2 = "1+2\n2+3";
  std::istringstream iss{simple2};
  Lexer lexer(iss);
  EXPECT_EQ(lexer.currentToken(), (Token{TokenType::NUM, "1"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::OPERATOR, "+"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "2"}));

  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NEW_LINE, "\n"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "2"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::OPERATOR, "+"}));
  EXPECT_EQ(lexer.nextToken(), (Token{TokenType::NUM, "3"}));
}

}