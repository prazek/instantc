#pragma once


#include <iterator>
#include "Token.h"
#include "Lexer.h"

class LexStream : std::iterator<std::forward_iterator_tag, const Token>{
  using Base = std::iterator<std::forward_iterator_tag, const Token>;

public:
  LexStream(Lexer &lexer) : lexer(lexer), current(lexer.currentToken()) {}
  Base::pointer operator->() const {
    return &current;
  }
  Base::reference operator*() const {
    return current;
  }
  // ++it
  LexStream operator++(int) {
    current = lexer.nextToken();
    return *this;
  }
  // it++
  LexStream operator++() {
    auto tmp = *this;
    this->operator++(42);
    return tmp;
  }
  /*
  bool operator==(const LexStream& rhs) { return ptr_ == rhs.ptr_; }
  bool operator!=(const LexStream& rhs) { return ptr_ != rhs.ptr_; }
*/
private:
  Lexer &lexer;
  Token current;
};

