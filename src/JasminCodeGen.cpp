#include "JasminCodeGen.h"
#include <cstdlib>

std::string JasminCodeGenVisitor::getPrelude() const {
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

antlrcpp::Any JasminCodeGenVisitor::visitProgram(InstantParser::ProgramContext *ctx) {
  variablesAllocator.visit(ctx);
  int localsLimit = variablesAllocator.numberOfVariables() + 1; // add main arg
  int stackLimit = stackHeightOptimizer.visit(ctx).as<int>();
  os << getPrelude();

  os << ".method public static main([Ljava/lang/String;)V\n"
    "  .limit locals " << localsLimit << "\n"
       "  .limit stack " << stackLimit << "\n";

  visitChildren(ctx);

  os <<"  return\n"
    ".end method\n";
  return {};
}

antlrcpp::Any JasminCodeGenVisitor::visitAssignExpr(InstantParser::AssignExprContext *ctx) {
  assert(ctx->children.size() == 3);

  visit(ctx->children.at(2));
  auto varName = ctx->children.at(0)->getText();

  auto stackPos = variablesAllocator.variablePosition(varName);
  if (0 <= stackPos && stackPos <= 3)
    os << "  istore_" << stackPos << "\n";
  else
    os << "  istore " << stackPos << "\n";
  return {};
}

antlrcpp::Any JasminCodeGenVisitor::visitSExpr(InstantParser::SExprContext *ctx) {
  visitChildren(ctx);
  os << "  invokestatic " << className << "/printInt(I)V\n";
  return {};
}

antlrcpp::Any JasminCodeGenVisitor::visitMulExpr(InstantParser::MulExprContext *ctx) {
  return handleOperator(ctx, "imul");
}

antlrcpp::Any JasminCodeGenVisitor::visitConstExpr(InstantParser::ConstExprContext *ctx) {
  auto value = atoll(ctx->getText().c_str());

  if (value == -1) {
    os << "  iconst_m1\n";
    return {};
  }

  auto isel = [](long long value) {
    if (0 <= value && value <= 5)
      return "iconst_";
    if (-128 <= value && value < 127)
      return "bipush ";
    if (-32768 <= value && value < 32767)
      return "sipush ";
    else
      return "ldc ";
  };

  os << "  " << isel(value) << value << "\n";
  return {};
}

antlrcpp::Any JasminCodeGenVisitor::visitDivExpr(InstantParser::DivExprContext *ctx) {
  return handleOperator(ctx, "idiv");
}
antlrcpp::Any JasminCodeGenVisitor::visitSubExpr(InstantParser::SubExprContext *ctx) {
  return handleOperator(ctx, "isub");
}

antlrcpp::Any JasminCodeGenVisitor::visitVarExpr(InstantParser::VarExprContext *ctx) {
  auto stackPos = variablesAllocator.variablePosition(ctx->getText());
  if (0 <= stackPos && stackPos <= 3)
    os << "  iload_" << stackPos << "\n";
  else
    os << "  iload " << stackPos << "\n";
  return {};
}

antlrcpp::Any JasminCodeGenVisitor::visitParensExpr(InstantParser::ParensExprContext *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any JasminCodeGenVisitor::visitAddExpr(InstantParser::AddExprContext *ctx) {
  return handleOperator(ctx, "iadd");
}

antlrcpp::Any JasminCodeGenVisitor::handleOperator(InstantParser::ExprContext *ctx,
                                          const std::string &opInst) {
  assert(ctx->children.size() == 3);
  visit(ctx->children.at(0));
  visit(ctx->children.at(2));
  if (dynamic_cast<SwapContext*>(ctx->parent))
    os << "  swap\n";
  os << "  " << opInst << '\n';
  return {};
}

antlrcpp::Any JasminCodeGenVisitor::visitSwap(SwapContext *ctx) {
  visitChildren(ctx);
  //os << "  swap\n"; // todo remove
  return {};
}


