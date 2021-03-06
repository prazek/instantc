#include "gtest/gtest.h"

#include "InstantLexer.h"
#include "antlr4-runtime.h"
#include "InstantLexer.h"
#include "InstantParser.h"
#include "StaticAnalysis.h"
#include "LLVMCodeGen.h"
#include "common.h"
#include <sstream>

using namespace antlr4;
static std::string getLLVMIR(std::string inputCode) {
  std::istringstream iss{inputCode};
  std::stringstream ss;

  ANTLRInputStream input(iss);
  InstantLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  InstantParser parser(&tokens);
  auto *ast = parser.program();

  Diagnostic diagnostic(std::move("Testing.ins"));
  StaticAnalysis staticAnalysis(diagnostic);
  staticAnalysis.visit(ast);

  LLVMCodeGen visitor(ss);
  visitor.visit(ast);

  return ss.str();
}
/*
TEST(LLVMCGTest, Simple) {
  const std::string simple = "a = 1 +2 * 3;a";
  auto out = getLLVMIR(simple);
  auto expected = LLVMCodeGen::prelude +
  "define i32 @main() {\n"
  "  %1 = mul i32 2, 3\n"
  "  %2 = add i32 1, %1\n"
  "  call void @printInt(i32 %2)\n\n"
  "  ret i32 0\n"
  "}\n";

  EXPECT_EQ(out, expected);
}
*/
TEST(LLVMCGTest, Complex) {
  const std::string complex =
    "a=0;b=1;c=0;d=1;e=0;f=1;g=0;h=1;\n"
    "a*b+c*d\n+e+f+g+h;\n"
    "a=1;b=2;c=1;d=2;e=1;f=2;g=1;h=2;i=1;j=2;k=1;l=2;m=1;n=2;\n"
    "(2*a+b/2+c+d+e+f+g+h+i+j/2+k+l+m+n)/10\n";
  auto out = getLLVMIR(complex);
  auto expected = LLVMCodeGen::prelude +
      "define i32 @main() {\n"
      "  %1 = mul i32 0, 1\n"
      "  %2 = mul i32 0, 1\n"
      "  %3 = add i32 0, 1\n"
      "  %4 = add i32 1, %3\n"
      "  %5 = add i32 0, %4\n"
      "  %6 = add i32 %2, %5\n"
      "  %7 = add i32 %1, %6\n"
      "  call void @printInt(i32 %7)\n"
      "\n"
      "  %8 = mul i32 2, 1\n"
      "  %9 = sdiv i32 2, 2\n"
      "  %10 = sdiv i32 2, 2\n"
      "  %11 = add i32 1, 2\n"
      "  %12 = add i32 2, %11\n"
      "  %13 = add i32 1, %12\n"
      "  %14 = add i32 %10, %13\n"
      "  %15 = add i32 1, %14\n"
      "  %16 = add i32 2, %15\n"
      "  %17 = add i32 1, %16\n"
      "  %18 = add i32 2, %17\n"
      "  %19 = add i32 1, %18\n"
      "  %20 = add i32 2, %19\n"
      "  %21 = add i32 1, %20\n"
      "  %22 = add i32 %9, %21\n"
      "  %23 = add i32 %8, %22\n"
      "  %24 = sdiv i32 %23, 10\n"
      "  call void @printInt(i32 %24)\n"
      "\n"
      "  ret i32 0\n"
      "}\n";

  EXPECT_EQ(out, expected);
}