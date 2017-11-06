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
  virtual std::ostream& print(std::ostream&) const = 0;
  void print() const;

  friend std::ostream &operator<<(std::ostream &os, const Expr& expr) {
    return expr.print(os);
  }
  virtual ~Expr() = 0;
};

struct VarExpr final : Expr  {
  VarExpr(std::string name) : name(std::move(name)) {}

  std::ostream& print(std::ostream& os) const override {
    return os << "VarExpr: " << name << '\n';
  }

  const std::string name;
};

struct ConstantExpr final : Expr {
  using data_type = long long;
  ConstantExpr(data_type value) : value(value) {}

  std::ostream& print(std::ostream& os) const override {
    return os << "ConstantExpr: " << value << '\n';
  }

  data_type value;
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

  std::ostream& print(std::ostream& os) const override {
    return os << "AssignExpr: " << variable << '\n';
  }

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