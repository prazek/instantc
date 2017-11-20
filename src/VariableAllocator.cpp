
#include "VariableAllocator.h"


antlrcpp::Any VariableAllocator::visitAssignExpr(InstantParser::AssignExprContext *ctx) {
  auto varName = ctx->children.at(0)->getText();
  if (variablePosition_.count(varName) == 0)
    variablePosition_[varName] = currentPosition++;
  return {};
}
