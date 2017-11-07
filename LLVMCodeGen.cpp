#include "LLVMCodeGen.h"
#include <ostream>
#include <cassert>


void LLVMCodeGen::emit(const AST &ast) {
  os << "declare void @printInt(i32)\n"
     << "define i32 @main() { \n";

  for (const auto &expr : ast.exprs) {
    if (auto *AE = dynamic_cast<const AssignExpr*>(expr.get()))
      emitAssignExpr(*AE);
    else {
      emitExpr(*expr);
      os << "\n";
    }
  }

  os << "ret 0\n"
     << "}\n";
}

std::string LLVMCodeGen::emitExpr(const Expr &expr) {
  if (auto *CE = dynamic_cast<const ConstantExpr*>(&expr))
    return emitConstant(*CE);
  if (auto *VE = dynamic_cast<const VarExpr*>(&expr))
    return emitVariableExpr(*VE);
  if (auto *BE = dynamic_cast<const BinaryExpr*>(&expr))
    return emitBinaryExpr(*BE);
  assert(false);
}



std::string LLVMCodeGen::emitConstant(const ConstantExpr &expr) {
  return std::to_string(expr.value);
}

std::string LLVMCodeGen::emitVariableExpr(const VarExpr &expr) {
  return "i32 %" + variables.at(expr.name);
}


void LLVMCodeGen::emitAssignExpr(const AssignExpr &expr) {
  auto rhs = emitExpr(*expr.rhs);
  auto value = currentVariable++;
  os << "%" << value << " = " << rhs;
  os << "\n";
  variables[expr.variable.name] = value;
}

std::string LLVMCodeGen::emitBinaryExpr(const BinaryExpr &expr) {
  auto lhs = emitExpr(*expr.lhs);
  auto rhs = emitExpr(*expr.rhs);
  auto newValue = currentVariable++;
  os << "%" << newValue << " = ";

  static const std::unordered_map<BinaryOperator, std::string> mapping = {
    {BinaryOperator::plus, "add"}, {BinaryOperator::minus, "sub"},
    {BinaryOperator::mul, "mul"}, {BinaryOperator::div, "div"}
  };

  os << mapping.at(expr.op) << " " << lhs << ", " << rhs << "\n";
  return "i32 " + std::to_string(newValue);
}
