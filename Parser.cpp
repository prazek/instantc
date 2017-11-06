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
      ast.exprs.push_back(parseStmt());
      break;
    case TokenType::OPERATOR:
      issueError("operator " + tok.string + " at begging of stmt");
      continue;
    case TokenType::NUM:
      ast.stmts.push_back(parseBasicStmt());
      continue;

    case TokenType::ASSIGN:
    case TokenType::INVALID:
      issueError("Wrong token at beggining");
      continue;
    case TokenType::SPACE:
      assert(false);
    }
    parseSemi();

  }
  out:

  return std::move(ast);
}

void Parser::issueError(const std::string& msg) {
  fprintf(stderr, "error: %s\n", msg.c_str());
}
static bool isEndStmt(TokenType type) {
  return type == TokenType::SEMI ||
      type == TokenType::NEW_LINE ||
      type == TokenType::END_FILE;
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
    return assignExpr;
  }

  if (lexStream->type == TokenType::OPERATOR)
    assert(false);

  if (isEndStmt(lexStream->type))
    return varExpr;

  assert(false);
  return Stmt();
}

void Parser::parseSemi() {
  if (!isEndStmt(lexStream->type))
      issueError("Semicolon or new line expected");

  ++lexStream;
}

Stmt Parser::parseBasicStmt() {
  auto expr = parseExpr();
  return Stmt{std::move(expr), parseSemi()};
}


std::unique_ptr<Expr> Parser::parseExpr() {
  auto first = parseBasicExpr();
  if (!first)
    return nullptr;


  static const std::unordered_map<char,

  // TODO handle binary ops
  return first;
}

std::unique_ptr<Expr> Parser::parseBasicExpr() {
  if (lexStream->type == TokenType::ID)
    return std::make_unique<VarExpr>((lexStream++)->string);
  if (lexStream->type == TokenType::NUM) {
    ConstantExpr::data_type val = std::stoi((lexStream++)->string);
    return std::make_unique<ConstantExpr>(val);
  }
  return nullptr;
}

