#pragma once
#include <string>
#include <memory>
#include <vector>
#include <sstream>

enum class BinaryOperator {
  plus,
  minus,
  mul,
  div
};

std::ostream &operator<<(std::ostream &os, BinaryOperator op);

BinaryOperator getOperator(char op);

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unique_ptr<T> &p) {
  if (p)
    return os << *p;
  return os << "null";
}


struct Expr {
  //Expr(const Expr&) = delete;
 //Expr(Expr&&) = delete;
  virtual std::ostream& print(std::ostream&) const = 0;
  void print() const;

  friend std::ostream &operator<<(std::ostream &os, const Expr& expr) {
    return expr.print(os);
  }
  virtual ~Expr() = 0;
protected:
  // Ugly for now.
  static int indentLevel;
};

struct VarExpr final : Expr  {
  VarExpr(std::string name) : name(std::move(name)) {}

  std::ostream& print(std::ostream& os) const override {
    return os << std::string(indentLevel, ' ') << "VarExpr: " << name << '\n';
  }

  const std::string name;
};

struct ConstantExpr final : Expr {
  using data_type = long long;
  ConstantExpr(data_type value) : value(value) {}

  std::ostream& print(std::ostream& os) const override {

    return os << std::string(indentLevel, ' ') << "ConstantExpr: " << value << '\n';
  }

  data_type value;
};

struct BinaryExpr final : Expr {
  std::unique_ptr<Expr> lhs, rhs;
  BinaryOperator op;

  BinaryExpr(std::unique_ptr<Expr> lhs, BinaryOperator op,
             std::unique_ptr<Expr> rhs) :
      lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {}

  std::ostream& print(std::ostream& os) const override {
    os << std::string(indentLevel, ' ') << "BinaryExpr: " << op << "\n";
    indentLevel += 2;
    os << std::string(indentLevel, ' ') << lhs
       << std::string(indentLevel, ' ') << rhs;
    indentLevel -= 2;
    return os;
  }
};

struct AssignExpr final : Expr{
  VarExpr variable;
  std::unique_ptr<Expr> rhs;

  AssignExpr(VarExpr varExpr, std::unique_ptr<Expr> rhs)
      : variable(std::move(varExpr)), rhs(std::move(rhs)) {}

  std::ostream& print(std::ostream& os) const override {
    os << std::string(indentLevel, ' ') << "AssignExpr: \n";
    indentLevel += 2;
    os << std::string(indentLevel, ' ') << variable << "\n"
       << std::string(indentLevel, ' ') << rhs << "\n";
    indentLevel -= 2;
    return os;
  }
};



struct AST {
  std::vector<std::unique_ptr<Expr> > exprs;

  friend std::ostream &operator<<(std::ostream& os, const AST &ast) {
    for (const auto &expr : ast.exprs)
      os << expr;
    return os;
  }

};