//
// Created by Piotr Padlewski on 11/18/17.
//

#include "Diagnostic.h"
void
Diagnostic::issueError(const std::string &msg, antlr4::ParserRuleContext *ctx) {

//  auto token = ctx->getStart()->getTokenSource()->getInputStream()->


  //ctx->getStart()->getTokenSource()->nextToken()
  //auto si = ctx->parent->getSourceInterval();
  std::cerr << fileName << ":"
    << ctx->getStart()->getLine() << ":"
    << ctx->getStart()->getCharPositionInLine() << ": error: " << msg << "\n";

  //< ctx->getStart()->getInputStream()->getText(si) << "\n";

  exit(1);
}
