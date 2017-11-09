#include "gtest/gtest.h"
#include "Lexer.h"
#include "LexStream.h"
#include "LLVMCodeGen.h"
#include "Parser.h"
#include <sstream>


static std::string getLLVMIR(std::string input) {
  std::istringstream iss{input};
  Lexer lexer(iss);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();
  std::stringstream ss;
  LLVMCodeGen cg(ss);
  cg.emit(ast);
  return ss.str();
}

TEST(LLVMCGTest, Simple) {
  const std::string simple = "a = 1 +2 * 3;a";
  auto out = getLLVMIR(simple);
  auto expected = LLVMCodeGen::prelude +
  "define i32 @main() {\n"
  "  %0 = i32 mul 2, 3\n"
  "  %1 = i32 add 1, %0\n"
  "  %2 = i32 %1\n"
  "  call void @printInt(i32 %2)\n\n"
  "  ret i32 0\n"
  "}\n";

  EXPECT_EQ(out, expected);
}

TEST(LLVMCGTest, Empty) {
  const std::string simple = "";
  auto out = getLLVMIR(simple);
  auto expected = LLVMCodeGen::prelude +
    "define i32 @main() {\n"
      "  ret i32 0\n"
      "}\n";

  EXPECT_EQ(out, expected);
}