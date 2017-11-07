
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
  ASSERT_EQ(ast.exprs.size(), 0ul);
}

TEST(ParserTest, Id) {
  std::string exprStr = "abc";

  std::istringstream iss{exprStr};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  ASSERT_EQ(ast.exprs.size(), 1ul);
  auto &expr = ast.exprs[0];
  ASSERT_NE(expr, nullptr);
  auto* var = dynamic_cast<VarExpr*>(expr.get());
  EXPECT_TRUE(var != nullptr);

  EXPECT_EQ(var->name, exprStr);
}

TEST(ParserTest, Num) {
  std::string exprNum = "42";

  std::istringstream iss{exprNum};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  ASSERT_EQ(ast.exprs.size(), 1ul);
  auto &expr = ast.exprs[0];
  ASSERT_NE(expr, nullptr);
  auto* var = dynamic_cast<ConstantExpr*>(expr.get());
  EXPECT_TRUE(var != nullptr);

  EXPECT_EQ(var->value, 42);
}

TEST(ParserTest, AssignExpr) {
  std::string exprNum = "a = 32";

  std::istringstream iss{exprNum};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  ASSERT_EQ(ast.exprs.size(), 1ul);
  auto &expr = ast.exprs[0];
  ASSERT_NE(expr, nullptr);
  auto* var = dynamic_cast<AssignExpr*>(expr.get());
  ASSERT_TRUE(var != nullptr);


  ASSERT_NE(var->rhs, nullptr);
  //todo rest

}

TEST(ParserTest, BinOp) {
  std::string exprNum = "42+32; \n 1 + 2 + 3 * 3";

  std::istringstream iss{exprNum};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  ASSERT_EQ(ast.exprs.size(), 1ul);
  auto &expr = ast.exprs[0];
  ASSERT_NE(expr, nullptr);
  auto* var = dynamic_cast<BinaryExpr*>(expr.get());
  ASSERT_TRUE(var != nullptr);
  EXPECT_EQ(var->op, BinaryOperator::plus);
  ASSERT_NE(var->lhs, nullptr);
  ASSERT_NE(var->rhs, nullptr);

  auto *lhs = dynamic_cast<ConstantExpr*>(var->lhs.get());
  ASSERT_NE(lhs, nullptr);
  EXPECT_EQ(lhs->value, 42);
  auto *rhs = dynamic_cast<ConstantExpr*>(var->rhs.get());
  ASSERT_NE(rhs, nullptr);
  EXPECT_EQ(rhs->value, 32);

}





