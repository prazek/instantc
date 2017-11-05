#pragma once
#include <string>
#include <memory>
#include <vector>

enum class BinaryOperator {
  plus,
  minus,
  assign,
  mul,
  div
};

struct Expr {
  //Expr(const Expr&) = delete;
 //Expr(Expr&&) = delete;
  virtual ~Expr() = 0;
};

struct VarExpr final : Expr  {
  VarExpr(std::string name) : name(std::move(name)) {}

  const std::string name;
  ~VarExpr() override = default;
};

struct ConstantExpr final : Expr {
  using data_type = long long;
  ConstantExpr(data_type var) : var(var) {}
  ~ConstantExpr() override = default;

  data_type var;
};

struct BinaryExpr final : Expr {
  BinaryExpr(std::unique_ptr<Expr> lhs, BinaryOperator op,
             std::unique_ptr<Expr> rhs) :
      lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {}

  std::unique_ptr<Expr> lhs, rhs;
  BinaryOperator op;
};

struct AssignExpr final : Expr{
  AssignExpr(VarExpr varExpr, std::unique_ptr<Expr> rhs)
      : variable(std::move(varExpr)), rhs(std::move(rhs)) {}
  ~AssignExpr() override = default;

  VarExpr variable;
  std::unique_ptr<Expr> rhs;
};

struct Stmt {
  std::unique_ptr<Expr> expr;
  bool withSemicolon;
};

struct AST {
  std::vector<Stmt> stmts;
};