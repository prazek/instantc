#include "AST.h"
#include <iostream>
#include <unordered_map>

int Expr::indentLevel;
Expr::~Expr() {}

void Expr::print() const {
  print(std::cerr);
}

BinaryOperator getOperator(char op) {
  static const std::unordered_map<char, BinaryOperator> mapping = {
    {'+', BinaryOperator::plus}, {'-', BinaryOperator::minus},
    {'*', BinaryOperator::mul}, {'/', BinaryOperator::div}
  };
  return mapping.at(op);
}
std::ostream &operator<<(std::ostream &os, BinaryOperator op) {
  static const std::unordered_map<BinaryOperator, char> mapping = {
    {BinaryOperator::plus, '+'}, {BinaryOperator::minus, '-'},
    {BinaryOperator::mul, '*'}, {BinaryOperator::div, '/'}
  };
  return os << mapping.at(op);
}
