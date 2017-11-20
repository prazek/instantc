#pragma once


#include "antlr4-runtime.h"
#include "InstantVisitor.h"
#include <string>


class  LLVMCodeGenVisitor : public InstantVisitor {
public:

  LLVMCodeGenVisitor(std::ostream &os) : os(os) {}

  antlrcpp::Any visitProgram(InstantParser::ProgramContext *ctx) override {
    os << prelude;
    os << "define i32 @main() {\n";
    auto res = visitChildren(ctx);
    os << "  ret i32 0\n"
       << "}\n";
    return res;
  }

  antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *ctx) override {
    assert(ctx->children.size() == 3);
    std::string rhs = visit(ctx->children.at(2));

    auto varName = ctx->children.at(0)->getText();
    variables_[varName] = rhs;
    return {};
  }

  antlrcpp::Any visitSExpr(InstantParser::SExprContext *ctx) override {
    assert(ctx->children.size() == 1);
    std::string expr = visit(ctx->children.at(0));
    os << "  call void @printInt(i32 " << expr << ")\n";
    os << "\n";
    return {};
  }

  antlrcpp::Any visitMulExpr(InstantParser::MulExprContext *ctx) override {
    return handleOperator(ctx, "mul");
  }

  antlrcpp::Any visitConstExpr(InstantParser::ConstExprContext *ctx) override {
    return ctx->getText();
  }

  antlrcpp::Any visitDivExpr(InstantParser::DivExprContext *ctx) override {
    return handleOperator(ctx, "sdiv");
  }

  antlrcpp::Any visitSubExpr(InstantParser::SubExprContext *ctx) override {
    return handleOperator(ctx, "sub");
  }

  antlrcpp::Any visitVarExpr(InstantParser::VarExprContext *ctx) override {
    return variables_.at(ctx->getText());
  }

  antlrcpp::Any visitParensExpr(InstantParser::ParensExprContext *ctx) override {
    assert(ctx->children.size() == 3);
    return visit(ctx->children.at(1));
  }

  antlrcpp::Any visitAddExpr(InstantParser::AddExprContext *ctx) override {
    return handleOperator(ctx, "add");
  }

  static const std::string prelude;

private:
  std::string handleOperator(InstantParser::ExprContext *ctx, const std::string &opInstr) {
    assert(ctx->children.size() == 3);

    std::string lhs = visit(ctx->children.at(0));
    std::string rhs = visit(ctx->children.at(2));

    auto newValue = currentVariable++;
    os << "  %" << newValue << " = " << opInstr << " i32 " << lhs << ", " << rhs << "\n";
    return "%" + std::to_string(newValue);
  }

private:
  std::unordered_map<std::string, std::string> variables_;
  unsigned long long currentVariable = 1;

  std::ostream &os;

};

