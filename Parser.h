

#pragma once
#include "AST.h"
#include "LexStream.h"

class Parser {
public:
  Parser(LexStream &lexStream) : lexStream(lexStream) {}

  AST runParser();
private:

  std::unique_ptr<Expr> parseStmt();
  std::unique_ptr<Expr> parseBasicStmt();
  std::unique_ptr<Expr> parseExpr();
  std::unique_ptr<Expr> parseBasicExpr();
  std::unique_ptr<Expr> parseBinOpRhs(std::unique_ptr<Expr> lhs,
                                      int precedence);


  std::nullptr_t issueError(const std::string &msg);
  void parseSemi();
private:
  AST ast;
  LexStream &lexStream;
};




