
#include "antlr4-runtime.h"
#include "InstantLexer.h"
#include "InstantParser.h"
#include "StaticAnalysis.h"
#include "LLVMCodeGenVisitor.h"
#include <iostream>


using namespace antlr4;

std::fstream openFile(const std::string &fileName) {
  std::fstream instantFile(fileName, std::ios_base::in);
  if (!instantFile.is_open()) {
    printf("Could not open file [%s]", fileName.c_str());
    exit(1);
  }
  return instantFile;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    printf("instant language compiler\n");
    printf("Usage: %s file.ins\n", argv[0]);
    exit(1);
  }
  std::string fileName = argv[1];
  auto file = openFile(argv[1]);

  ANTLRInputStream input(file);
  InstantLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();


  InstantParser parser(&tokens);
  auto program = parser.program();

  {
    Diagnostic diagnostic(fileName);
    //StaticAnalysis staticAnalysis(diagnostic);
    //staticAnalysis.visit(program);
  }
  LLVMCodeGenVisitor visitor(std::cout);
  visitor.visit(program);
  std::cout.flush();
  //tree::ParseTreeWalker::DEFAULT.walk(&visitor, program);

  return 0;
}

