#pragma once

#include "antlr4-runtime.h"
#include "InstantLexer.h"
#include "InstantParser.h"
#include "StaticAnalysis.h"
#include "LLVMCodeGenVisitor.h"
#include <iostream>


using namespace antlr4;

inline InstantParser::ProgramContext* getAST(std::istream& file,
                                      std::string fileName) {
  ANTLRInputStream input(file);
  InstantLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  InstantParser parser(&tokens);
  auto program = parser.program();

  Diagnostic diagnostic(std::move(fileName));
  StaticAnalysis staticAnalysis(diagnostic);
  staticAnalysis.visit(program);
  return program;
}