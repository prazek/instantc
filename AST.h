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

template <typename T>
std::ostream &printOpt(std::ostream &os, const T &ptr) {
  if (ptr)
    return os << *ptr;
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
    return os << std::string(indentLevel, " ") << "VarExpr: " << name << '\n';
  }

  const std::string name;
};

struct ConstantExpr final : Expr {
  using data_type = long long;
  ConstantExpr(data_type value) : value(value) {}

  std::ostream& print(std::ostream& os) const override {

    return os << std::string(indentLevel, " ") << "ConstantExpr: " << value << '\n';
  }

  data_type value;
};

struct BinaryExpr final : Expr {
  BinaryExpr(std::unique_ptr<Expr> lhs, BinaryOperator op,
             std::unique_ptr<Expr> rhs) :
      lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {}

  std::ostream& print(std::ostream& os) const override {
    os << std::string(indentLevel, " ") << "BinaryExpr: \n";
    indentLevel += 2;
    os << std::string(indentLevel, " ") << printOpt(os, lhs) << "\n"
       << std::string(indentLevel, " ") << printOpt(os, rhs) << "\n";
    indentLevel -= 2;
    return os;
  }


  std::unique_ptr<Expr> lhs, rhs;
  BinaryOperator op;
};

struct AssignExpr final : Expr{
  AssignExpr(VarExpr varExpr, std::unique_ptr<Expr> rhs)
      : variable(std::move(varExpr)), rhs(std::move(rhs)) {}

  std::ostream& print(std::ostream& os) const override {
    os << std::string(indentLevel, " ") << "AssignExpr: \n";
    indentLevel += 2;
    os << std::string(indentLevel, " ") << variable << "\n"
       << std::string(indentLevel, " ") << printOpt(os, rhs) << "\n";
    indentLevel -= 2;
    return os;
  }

  VarExpr variable;
  std::unique_ptr<Expr> rhs;
};



struct AST {
  std::vector<std::unique_ptr<Expr> > exprs;
};