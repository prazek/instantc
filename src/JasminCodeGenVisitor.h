#pragma once

#include "antlr4-runtime.h"
#include "InstantVisitor.h"
#include "VariableAllocator.h"
#include "StackHeightOptimizer.h"

class  JasminCodeGenVisitor : public InstantVisitor {
public:
  JasminCodeGenVisitor(std::ostream &os, std::string className)
    : os(os),
      className(std::move(className)) {}

  std::string getPrelude() const;
  antlrcpp::Any visitProgram(InstantParser::ProgramContext *ctx) override;
  antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *ctx) override;
  antlrcpp::Any visitSExpr(InstantParser::SExprContext *ctx) override;
  antlrcpp::Any visitMulExpr(InstantParser::MulExprContext *ctx) override;
  antlrcpp::Any visitConstExpr(InstantParser::ConstExprContext *ctx) override;
  antlrcpp::Any visitDivExpr(InstantParser::DivExprContext *ctx) override;
  antlrcpp::Any visitSubExpr(InstantParser::SubExprContext *ctx) override;
  antlrcpp::Any visitVarExpr(InstantParser::VarExprContext *ctx) override;
  antlrcpp::Any visitParensExpr(InstantParser::ParensExprContext *ctx) override;
  antlrcpp::Any visitAddExpr(InstantParser::AddExprContext *ctx) override;

private:
  antlrcpp::Any handleOperator(InstantParser::ExprContext *ctx, const std::string &opInst);
  VariableAllocator variablesAllocator;
  StackHeightOptimizer stackHeightOptimizer;
  std::ostream &os;
  std::string className;
};

