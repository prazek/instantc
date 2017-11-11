#include "gtest/gtest.h"
#include "Lexer.h"
#include "LexStream.h"
#include "JasminCodeGen.h"
#include "Parser.h"
#include <sstream>

static std::string prelude;

static std::string getLLVMIR(std::string input) {
  std::istringstream iss{input};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  std::stringstream ss;
  JasminCodeGen cg(ss, "Test");
  prelude = cg.getPrelude();
  cg.emit(ast);
  return ss.str();
}

TEST(JasminCGTest, Simple) {
  const std::string simple = "a = 1 +2 * 3;a";
  auto out = getLLVMIR(simple);
  auto expected = prelude +
    ".method public static main([Ljava/lang/String;)V\n"
    "  .limit locals 1\n"
    "  .limit stack 3\n"
    "  iconst_2\n"
    "  iconst_3\n"
    "  imul\n"
    "  iconst_1\n"
    "  iadd\n"
    "  istore 0\n"
    "  iload 0\n"
    "  invokestatic x/printInt(I)V\n"
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
  auto out = getLLVMIR(complex);
  auto expected = prelude +
      ".method public static main([Ljava/lang/String;)V\n"
      "  .limit locals 2\n"
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
      "  invokestatic x/printInt(I)V\n"
      "  iload 0\n"
      "  iload 1\n"
      "  imul\n"
      "  iconst_2\n"
      "  iconst_2\n"
      "  iadd\n"
      "  iadd\n"
      "  invokestatic x/printInt(I)V\n"
      "  return\n"
      ".end method\n";

  EXPECT_EQ(out, expected);
}