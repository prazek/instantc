#include "AST.h"
#include <iostream>

Expr::~Expr() {}
void Expr::print() const {
  print(std::cerr);
}

