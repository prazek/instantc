
// Generated from Instant.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "InstantVisitor.h"
#include "CommonTokenStream.h"
#include "TokenSource.h"
#include "CommonToken.h"
#include "TokenStream.h"
#include "Diagnostic.h"

#include <iostream>

/**
 * This class provides an empty implementation of InstantVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  StaticAnalysis : public InstantVisitor {
public:

  StaticAnalysis(Diagnostic &diagnostic) : diagnostic(diagnostic) {}

  virtual antlrcpp::Any visitProgram(InstantParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *ctx) override {
    assert(ctx->children.size() == 3);
    visit(ctx->children[2]);

    auto varName = ctx->children[0]->getText();

    knownVariables.insert(varName);
    return {};
  }

  virtual antlrcpp::Any visitSExpr(InstantParser::SExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulExpr(InstantParser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstExpr(InstantParser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDivExpr(InstantParser::DivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubExpr(InstantParser::SubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarExpr(InstantParser::VarExprContext *ctx) override {
    assert(ctx->children.size() == 1);

    auto varName = ctx->children[0]->getText();
    if (knownVariables.count(varName) == 0) {
      diagnostic.issueError("variable '" + varName + "' used before initialization", ctx);
    }
    return {};
  }

  virtual antlrcpp::Any visitParensExpr(InstantParser::ParensExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddExpr(InstantParser::AddExprContext *ctx) override {
    return visitChildren(ctx);
  }


private:
  std::set<std::string> knownVariables;
  Diagnostic& diagnostic;
};

