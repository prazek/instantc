
#include "StackHeightOptimizer.h"
antlrcpp::Any StackHeightOptimizer::visitAssignExpr(InstantParser::AssignExprContext *ctx) {
  return visit(ctx->children.at(2)).as<int>();
}
