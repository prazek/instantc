

#pragma once
#include "AST.h"
#include "LexStream.h"

class Parser {
public:
  Parser(LexStream &lexStream) : lexStream(lexStream) {}

  AST runParser();
private:

  Stmt parseStmt();
  Stmt parseBasicStmt();
  std::unique_ptr<Expr> parseExpr();
  std::unique_ptr<Expr> parseBasicExpr();

  void issueError(const std::string &msg);
  void parseSemi();
private:
  AST ast;
  LexStream &lexStream;
};




