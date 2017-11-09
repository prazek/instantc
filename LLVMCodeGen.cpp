#include "LLVMCodeGen.h"
#include <ostream>
#include <cassert>

const std::string LLVMCodeGen::prelude =
  "@dnl = internal constant [4 x i8] c\"%d\\0A\\00\"\n"
  "declare i32 @printf(i8*, ...)\n"
  " \n"
  "define void @printInt(i32 %x) {\n"
  "  %t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0\n"
  "  call i32 (i8*, ...) @printf(i8* %t0, i32 %x)\n"
  "  ret void\n"
  "}\n";

void LLVMCodeGen::emit(const AST &ast) {
  os << prelude;

  os << "define i32 @main() {\n";

  for (const auto &expr : ast.exprs) {
    //os << "  ";
    if (auto *AE = dynamic_cast<const AssignExpr*>(expr.get()))
      emitAssignExpr(*AE);
    else {
      auto e = emitExpr(*expr);
      os << "  call void @printInt(i32 " << e << ")\n";
      os << "\n";
    }
  }

  os << "  ret i32 0\n"
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
  return "%" + variables.at(expr.name);
}


void LLVMCodeGen::emitAssignExpr(const AssignExpr &expr) {
  auto rhs = emitExpr(*expr.rhs);
  auto value = currentVariable++;
  os << "  %" << value << " = i32 " << rhs;
  os << "\n";
  variables[expr.variable.name] = std::to_string(value);
}

std::string LLVMCodeGen::emitBinaryExpr(const BinaryExpr &expr) {
  auto lhs = emitExpr(*expr.lhs);
  auto rhs = emitExpr(*expr.rhs);
  auto newValue = currentVariable++;
  os << "  %" << newValue << " = ";

  static const std::unordered_map<BinaryOperator, std::string> mapping = {
    {BinaryOperator::plus, "add"}, {BinaryOperator::minus, "sub"},
    {BinaryOperator::mul, "mul"}, {BinaryOperator::div, "div"}
  };

  os << "i32 " << mapping.at(expr.op) << " " << lhs << ", " << rhs << "\n";
  return "%" + std::to_string(newValue);
}
