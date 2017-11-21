#include "JasminVisitor.h"

antlrcpp::Any SwapContext::accept(antlr4::tree::ParseTreeVisitor  *visitor) {
  if (auto parserVisitor = dynamic_cast<JasminVisitor*>(visitor))
    return parserVisitor->visitSwap(this);
  else
    return visitor->visitChildren(this);

}

SwapContext::SwapContext(InstantParser::ExprContext *) {
}
