
#include "JasminCodeGen.h"
#include <cassert>
#include <utility>

std::string JasminCodeGen::getPrelude() {
  return ".class public " + className + "\n"
      ".super java/lang/Object\n"
      "\n"
      ".method public <init>()V\n"
      "  aload_0\n"
      "  invokespecial java/lang/Object/<init>()V\n"
      "  return\n"
      ".end method\n"
      "\n"
      ".method public static printInt(I)V \n"
      "    .limit locals 10\n"
      "    .limit stack 10\n"
      "    iload 0\n"
      "    getstatic java/lang/System/out Ljava/io/PrintStream; \n"
      "    swap\n"
      "    invokevirtual java/io/PrintStream/println(I)V \n"
      "    return\n"
      ".end method\n"
      "\n";
}

void JasminCodeGen::emit(AST &ast) {

  int stackLimit = optimizeStackHeight(ast);
  int localsLimit = allocateLocalVariables(ast) + 1;

  os << getPrelude();

  os << ".method public static main([Ljava/lang/String;)V\n"
    "  .limit locals " << localsLimit << "\n"
    "  .limit stack " << stackLimit << "\n";

  for (const auto &expr : ast.exprs) {
    //os << "  ";
    if (auto *AE = dynamic_cast<const AssignExpr*>(expr.get()))
      emitAssignExpr(*AE);
    else {
      emitExpr(*expr);
      os << "  invokestatic " << className + "/printInt(I)V\n";
    }
  }

  os <<"  return\n"
       ".end method\n";
}
void JasminCodeGen::emitAssignExpr(const AssignExpr &expr) {
  emitExpr(*expr.rhs);

  os << "  istore " << localVariables.at(expr.variable.name) << "\n";

}
void JasminCodeGen::emitExpr(const Expr &expr) {
  if (auto *CE = dynamic_cast<const ConstantExpr*>(&expr))
    return emitConstant(*CE);
  if (auto *VE = dynamic_cast<const VarExpr*>(&expr))
    return emitVariableExpr(*VE);
  if (auto *BE = dynamic_cast<const BinaryExpr*>(&expr))
    return emitBinaryExpr(*BE);
  assert(false);
}

void JasminCodeGen::emitBinaryExpr(const BinaryExpr &expr) {
  emitExpr(*expr.lhs);
  emitExpr(*expr.rhs);
  static const std::unordered_map<BinaryOperator, std::string> mapping = {
    {BinaryOperator::plus, "iadd"}, {BinaryOperator::minus, "isub"},
    {BinaryOperator::mul, "imul"}, {BinaryOperator::div, "idiv"}
  };

  os << "  " << mapping.at(expr.op) << "\n";
}

void JasminCodeGen::emitVariableExpr(const VarExpr &expr) {
  os << "  iload " << localVariables.at(expr.name) << "\n";
}

void JasminCodeGen::emitConstant(const ConstantExpr &expr) {
  if (0 <= expr.value && expr.value <= 4)
    os << "  iconst_" << expr.value << "\n";
  else
    os << "  ldc " << expr.value << "\n";
}


int JasminCodeGen::allocateLocalVariables(const AST &ast) {
  int localsCount = 0;
  for (const auto &expr : ast.exprs) {
    if (auto *AE = dynamic_cast<const AssignExpr*>(expr.get())){
      if (localVariables.count(AE->variable.name) == 0) {
        localVariables[AE->variable.name] = localsCount++;
      }

    }

  }

  return localsCount;
}
int JasminCodeGen::optimizeStackHeight(AST &ast) {
  int result = 0;
  for (const auto &expr : ast.exprs) {
    result = std::max(result, optimizeExprStackHeight(*expr));
  }
  return result;
}
int JasminCodeGen::optimizeExprStackHeight(Expr &expr) {
  if (dynamic_cast<ConstantExpr *>(&expr))
  return 1;
  if (dynamic_cast<VarExpr *>(&expr))
  return 1;
  if (auto *BE = dynamic_cast<BinaryExpr *>(&expr)) {
    int lhsHeight = optimizeExprStackHeight(*BE->lhs);
    int rhsHeight = optimizeExprStackHeight(*BE->rhs);
    if (lhsHeight < rhsHeight &&
      (BE->op == BinaryOperator::plus || BE->op == BinaryOperator::mul)) {
      std::swap(BE->lhs, BE->rhs);
    }
    return std::max(lhsHeight, 1 + rhsHeight);
  }
  if (auto *AE = dynamic_cast<AssignExpr*>(&expr)) {
    return optimizeExprStackHeight(*AE->rhs);
  }
  assert(false);
}
