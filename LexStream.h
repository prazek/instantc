#pragma once


#include <iterator>
#include "Token.h"
#include "Lexer.h"

class LexStream : std::iterator<std::forward_iterator_tag, const Token>{
  using Base = std::iterator<std::forward_iterator_tag, const Token>;
  LexStream(Lexer &lexer) : lexer(lexer) {}
public:




  Base::reference operator*() const {
    return lexer.currentToken();
  }
  // ++it
  Base::reference operator++(int) {
    return lexer.nextToken();
  }
  // it++
  Base::value_type operator++() {
    Token token = this->operator*();
    this->operator++(42);
    return token;
  }

private:
  Lexer &lexer;
};

