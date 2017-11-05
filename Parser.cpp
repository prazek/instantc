#include "Parser.h"


AST Parser::runParser() {
  const Token &tok = *lexStream;

  while (1) {

    switch(tok.type) {
    case TokenType::END_FILE:
      goto out;
    case TokenType::SEMI:
    case TokenType::NEW_LINE:
      continue;
    case TokenType::ID:
      ast.stmts.push_back(parseStmt());

    case TokenType::OPERATOR:
      issueError("operator " + tok.string + " at begging of stmt");
    case TokenType::NUM:
      ast.stmts.push_back(parseBasicStmt());


    case TokenType::ASSIGN:
    case TokenType::INVALID:
      issueError("Wrong token at beggining");
    case TokenType::SPACE:
      assert(false);
    }


  }
  out:

  return std::move(ast);
}

void Parser::issueError(const std::string& msg) {
  printf("error: %s", msg.c_str());
}

// id = expr
// | expr
Stmt Parser::parseStmt() {
  auto varExpr = std::make_unique<VarExpr>(lexStream->string);
  ++lexStream;
  if (lexStream->type == TokenType::ASSIGN) {
    auto rhs = parseExpr();
    auto assignExpr = std::make_unique<AssignExpr>(std::move(*varExpr),
                                                   std::move(rhs));
    return Stmt{std::move(assignExpr), parseSemi()};
  }
  else {
    assert(false);
  }


  return Stmt();
}

bool Parser::parseSemi() {
  bool isSemi = lexStream->type == TokenType::SEMI;
  if (!isSemi && lexStream->type != TokenType::NEW_LINE) {
      issueError("Semicolon or new line expected");
    }
  lexStream++;
  return isSemi;
}

Stmt Parser::parseBasicStmt() {
  auto expr = parseExpr();
  return Stmt{std::move(expr), parseSemi()};
}


std::unique_ptr<Expr> Parser::parseExpr() {
  auto first = parseBasicExpr();
  if (!first)
    return nullptr;
  // TODO handle binary ops
  return nullptr;
}

std::unique_ptr<Expr> Parser::parseBasicExpr() {
  if (lexStream->type == TokenType::ID)
    return std::make_unique<VarExpr>(lexStream++->string);
  if (lexStream->type == TokenType::NUM)
    return std::make_unique<ConstantExpr>(
        std::atoll(lexStream++->string.c_str()));
  return nullptr;
}

