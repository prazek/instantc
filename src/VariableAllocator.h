#pragma once


#include "DefaultVisitor.h"
#include <unordered_map>
#include <string>

class  VariableAllocator : public DefaultVisitor {
public:

  antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *ctx) override;

  int variablePosition(const std::string &varName) const {
    return variablePosition_.at(varName);
  }

  int numberOfVariables() const { return currentPosition; }
private:
  std::unordered_map<std::string, int> variablePosition_;
  int currentPosition = 0;
};
