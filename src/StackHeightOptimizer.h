#pragma once


#include "DefaultVisitor.h"
#include <unordered_map>
#include <string>

class  StackHeightOptimizer : public DefaultVisitor {
public:

  antlrcpp::Any visitProgram(InstantParser::ProgramContext *ctx) override {
    int result = 0;
    for (auto *children : ctx->children) {
      result = std::max(result, visit(children).as<int>());
    }
    return result;
  }
  antlrcpp::Any visitTerminal(antlr4::tree::TerminalNode * /*node*/) override {
    return 0;
  }
  antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *ctx) override;
  antlrcpp::Any visitMulExpr(InstantParser::MulExprContext *ctx) override {
    return handleOperator(ctx, true);
  }

  antlrcpp::Any visitConstExpr(InstantParser::ConstExprContext *) override {
    return 1;
  }

  antlrcpp::Any visitDivExpr(InstantParser::DivExprContext *ctx) override {
    return handleOperator(ctx, true);
  }

  antlrcpp::Any visitSubExpr(InstantParser::SubExprContext *ctx) override {
    return handleOperator(ctx, false);
  }

  antlrcpp::Any visitVarExpr(InstantParser::VarExprContext *) override {
    return 1;
  }

  antlrcpp::Any visitParensExpr(InstantParser::ParensExprContext *ctx) override {
    assert(ctx->children.size() == 3);
    return visit(ctx->children.at(1)).as<int>();
  }

  antlrcpp::Any visitAddExpr(InstantParser::AddExprContext *ctx) override {
    return handleOperator(ctx, true);
  }

private:
  int handleOperator(InstantParser::ExprContext *ctx, bool alternativeOp) {
    assert(ctx->children.size() == 3);
    auto &lhs = ctx->children.at(0);
    int lhsHeight = visit(lhs);
    auto &rhs = ctx->children.at(2);
    int rhsHeight = visit(rhs);
    if (lhsHeight < rhsHeight && alternativeOp) {
      std::swap(lhs, rhs);
    }
    return std::max(lhsHeight, 1 + rhsHeight);
  }

};
