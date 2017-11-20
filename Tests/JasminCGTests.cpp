#include "gtest/gtest.h"
#include "antlr4-runtime.h"
#include "common.h"
#include "JasminCodeGenVisitor.h"

#include "InstantLexer.h"
#include "StaticAnalysis.h"
#include <sstream>

static std::string prelude;
using namespace antlr4;

static std::string getJasmin(std::string inputCode) {
  std::istringstream iss(inputCode);
  std::stringstream ss;

  ANTLRInputStream input(iss);
  InstantLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  InstantParser parser(&tokens);
  auto *ast = parser.program();

  Diagnostic diagnostic(std::move("Test.ins"));
  StaticAnalysis staticAnalysis(diagnostic);
  staticAnalysis.visit(ast);


  JasminCodeGenVisitor cg(ss, "Test");
  cg.visit(ast);

  prelude = cg.getPrelude();
  return ss.str();
}

TEST(JasminCGTest, Simple) {

  const std::string simple = "a = 1 +2 * 3;a ";
  auto out = getJasmin(simple);
  auto expected = prelude +
    ".method public static main([Ljava/lang/String;)V\n"
    "  .limit locals 2\n"
    "  .limit stack 3\n"
    "  iconst_2\n"
    "  iconst_3\n"
    "  imul\n"
    "  iconst_1\n"
    "  iadd\n"
    "  istore 0\n"
    "  iload 0\n"
    "  invokestatic Test/printInt(I)V\n"
    "  return\n"
    ".end method\n";

  EXPECT_EQ(out, expected);
}

TEST(JasminCGTest, Complex) {
  const std::string complex =
    "a=1;\n"
    "b=2;\n"
    "2+2*2;\n"
    "a*b+2+2";
  auto out = getJasmin(complex);
  auto expected = prelude +
      ".method public static main([Ljava/lang/String;)V\n"
      "  .limit locals 3\n"
      "  .limit stack 3\n"
      "  iconst_1\n"
      "  istore 0\n"
      "  iconst_2\n"
      "  istore 1\n"
      "  iconst_2\n"
      "  iconst_2\n"
      "  imul\n"
      "  iconst_2\n"
      "  iadd\n"
      "  invokestatic Test/printInt(I)V\n"
      "  iload 0\n"
      "  iload 1\n"
      "  imul\n"
      "  iconst_2\n"
      "  iconst_2\n"
      "  iadd\n"
      "  iadd\n"
      "  invokestatic Test/printInt(I)V\n"
      "  return\n"
      ".end method\n";

  EXPECT_EQ(out, expected);
}

TEST(JasminCGTest, Sub) {
  std::string input =
    "a=1;\n"
    "(2+a)/(1-(a+1))+a;\n"
    "1-1-1;";
  auto out = getJasmin(input);
  auto expected = prelude +
    ".method public static main([Ljava/lang/String;)V\n"
    "  .limit locals 2\n"
    "  .limit stack 4\n"
    "  iconst_1\n"
    "  istore 0\n"
    "  iconst_1\n"
    "  iload 0\n"
    "  iconst_1\n"
    "  iadd\n"
    "  isub\n"
    "  iconst_2\n"
    "  iload 0\n"
    "  iadd\n"
    "  idiv\n"
    "  iload 0\n"
    "  iadd\n"
    "  invokestatic Test/printInt(I)V\n"
    "  iconst_1\n"
    "  iconst_1\n"
    "  isub\n"
    "  iconst_1\n"
    "  isub\n"
    "  invokestatic Test/printInt(I)V\n"
    "  return\n"
    ".end method\n";

  EXPECT_EQ(out, expected);
}