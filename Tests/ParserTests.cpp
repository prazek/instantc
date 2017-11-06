
#include "gtest/gtest.h"
#include "Lexer.h"
#include "LexStream.h"
#include "Parser.h"
#include <sstream>


TEST(ParserTest, Empty) {
  std::string empty = "";

  std::istringstream iss{empty};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();
  ASSERT_EQ(ast.stmts.size(), 0ul);
}

TEST(ParserTest, Id) {
  std::string expr = "abc";

  std::istringstream iss{expr};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  ASSERT_EQ(ast.stmts.size(), 1ul);
  auto &stmt = ast.stmts[0];
  ASSERT_NE(stmt.expr, nullptr);
  auto* var = dynamic_cast<VarExpr*>(stmt.expr.get());
  EXPECT_TRUE(var != nullptr);

  EXPECT_EQ(var->name, expr);
}

TEST(ParserTest, Num) {
  std::string expr = "42";

  std::istringstream iss{expr};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  ASSERT_EQ(ast.stmts.size(), 1ul);
  auto &stmt = ast.stmts[0];
  ASSERT_NE(stmt.expr, nullptr);
  auto* var = dynamic_cast<ConstantExpr*>(stmt.expr.get());
  EXPECT_TRUE(var != nullptr);

  EXPECT_EQ(var->value, 42);
}



