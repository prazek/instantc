#pragma once

#include "AST.h"
#include <unordered_map>
#include <iosfwd>
#include <string>

class LLVMCodeGen {
public:
  LLVMCodeGen(std::ostream &os) : os(os) {}

  void emit(const AST& ast);

  void emitAssignExpr(const AssignExpr &expr);
  std::string emitExpr(const Expr &expr);
  std::string emitBinaryExpr(const BinaryExpr &expr);
  std::string emitConstant(const ConstantExpr &expr);
  std::string emitVariableExpr(const VarExpr &expr);


private:
  std::string getNewValue();
  std::unordered_map<std::string, std::string> variables;
  int currentVariable = 0;
  std::ostream &os;
};



