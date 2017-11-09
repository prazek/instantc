#include "Parser.h"
#include <unordered_map>

AST Parser::runParser() {
  const Token &tok = *lexStream;

  while (1) {

    switch(tok.type) {
    case TokenType::END_FILE:
      goto out;
    case TokenType::SEMI:
      break;
    case TokenType::ID:
      ast.exprs.emplace_back(parseStmt());
      break;
    case TokenType::OPERATOR:
      issueError("operator " + tok.string + " at begging of stmt");
      break;
    case TokenType::NUM:
      ast.exprs.emplace_back(parseBasicStmt());
      break;

    case TokenType::ASSIGN:
    case TokenType::INVALID:
      issueError("Wrong token at beggining");
      break;
    case TokenType::SPACE:
      assert(false);
    }
    parseSemi();

  }
  out:

  return std::move(ast);
}

std::nullptr_t Parser::issueError(const std::string& msg) {
  fprintf(stderr, "error: %s\n", msg.c_str());
  return nullptr;
}
static bool isEndStmt(TokenType type) {
  return type == TokenType::SEMI ||
      type == TokenType::END_FILE;
}

// id = expr
// id op expr
std::unique_ptr<Expr> Parser::parseStmt() {
  auto varExpr = std::make_unique<VarExpr>(lexStream->string);
  ++lexStream;
  if (lexStream->type == TokenType::ASSIGN) {
    ++lexStream;
    auto rhs = parseExpr();
    return std::make_unique<AssignExpr>(std::move(*varExpr),
                                                   std::move(rhs));
  }

  if (lexStream->type == TokenType::OPERATOR)
    return parseBinOpRhs(std::move(varExpr), 0);

  if (isEndStmt(lexStream->type))
    return std::move(varExpr);

  assert(false);
  return nullptr;
}

void Parser::parseSemi() {
  if (!isEndStmt(lexStream->type))
      issueError("Semicolon or new line expected");
  if (lexStream->type != TokenType::END_FILE)
    ++lexStream;
}

std::unique_ptr<Expr> Parser::parseBasicStmt() {
  return parseExpr();
}


std::unique_ptr<Expr> Parser::parseExpr() {
  auto first = parseBasicExpr();
  if (!first)
    return nullptr;

  return parseBinOpRhs(std::move(first), 0);
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


std::unique_ptr<Expr> Parser::parseBinOpRhs(std::unique_ptr<Expr> lhs,
                                            int startPrec) {



  static const std::unordered_map<char, int8_t> operatorPrecedence = {
    {'+', 10}, {'-', 10}, {'/', 20}, {'*', 30}
  };

  while (true) {
    if (isEndStmt(lexStream->type))
      return lhs;

    if (lexStream->type != TokenType::OPERATOR)
      return issueError("Expected operator after expression");

    assert(lexStream->type == TokenType::OPERATOR);
    assert(lexStream->string.size() == 1);
    char operatorChar = lexStream->string[0];
    auto prec = operatorPrecedence.at(operatorChar);
    if (prec < startPrec)
      return lhs;

    ++lexStream;
    auto rhs = parseBasicExpr();
    if (!rhs)
      return issueError("Expected expression after operator");


    if (isEndStmt(lexStream->type))
      return std::make_unique<BinaryExpr>(std::move(lhs),
                                          getOperator(operatorChar),
                                          std::move(rhs));

    if (lexStream->type != TokenType::OPERATOR)
      return issueError("Expected operator after expression");

    assert(lexStream->type == TokenType::OPERATOR);
    assert(lexStream->string.size() == 1);
    char operatorChar2 = lexStream->string[0];
    auto prec2 = operatorPrecedence.at(operatorChar2);
    if (prec < prec2 || (operatorChar == '+' && operatorChar2 == '+')) {
      rhs = parseBinOpRhs(std::move(rhs), prec2);
      if (!rhs)
        return nullptr;
    }
    // Merge LHS/RHS.
    lhs = std::make_unique<BinaryExpr>(std::move(lhs),
                                       getOperator(operatorChar),
                                       std::move(rhs));

  }
  assert(false);
}

