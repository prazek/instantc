#pragma once
#include "AST.h"
#include <iosfwd>
#include <string>
#include <unordered_map>

class JasminCodeGen {
public:
  JasminCodeGen(std::ostream &os) : os(os) {}

  void emit(AST& ast);

  void emitAssignExpr(const AssignExpr &expr);
  void emitExpr(const Expr &expr);
  void emitBinaryExpr(const BinaryExpr &expr);
  void emitConstant(const ConstantExpr &expr);
  void emitVariableExpr(const VarExpr &expr);

  int allocateLocalVariables(const AST &ast);
  int optimizeStackHeight(AST &ast);
  int optimizeExprStackHeight(Expr &expr);
  static const std::string prelude;
private:
  std::unordered_map<std::string, int> localVariables;
  std::ostream &os;
};


