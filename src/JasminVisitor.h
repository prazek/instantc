
#pragma once


#include "InstantVisitor.h"

class SwapContext : public InstantParser::ExprContext {
public:
  SwapContext(InstantParser::ExprContext *ctx);

  antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
};




class  JasminVisitor : public InstantVisitor {
public:
  virtual antlrcpp::Any visitSwap(SwapContext *context) = 0;
};
