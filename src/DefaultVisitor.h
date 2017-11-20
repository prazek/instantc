#pragma once

#include "antlr4-runtime.h"
#include "JasminVisitor.h"

class  DefaultVisitor : public JasminVisitor {
public:

  antlrcpp::Any visitProgram(InstantParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *ctx) override {
    assert(ctx->children.size() == 3);
    return visitChildren(ctx);
  }

  antlrcpp::Any visitSExpr(InstantParser::SExprContext *ctx) override {
    assert(ctx->children.size() == 1);
    return visitChildren(ctx);
  }

  antlrcpp::Any visitMulExpr(InstantParser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitConstExpr(InstantParser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitDivExpr(InstantParser::DivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitSubExpr(InstantParser::SubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitVarExpr(InstantParser::VarExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitParensExpr(InstantParser::ParensExprContext *ctx) override {
    assert(ctx->children.size() == 3);
    return visit(ctx->children.at(1));
  }

  antlrcpp::Any visitAddExpr(InstantParser::AddExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitSwap(SwapContext *ctx) override {
    return visitChildren(ctx);
  }

};

