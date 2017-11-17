
// Generated from Instant.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "InstantParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by InstantParser.
 */
class  InstantListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(InstantParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(InstantParser::ProgramContext *ctx) = 0;

  virtual void enterAssignExpr(InstantParser::AssignExprContext *ctx) = 0;
  virtual void exitAssignExpr(InstantParser::AssignExprContext *ctx) = 0;

  virtual void enterSExpr(InstantParser::SExprContext *ctx) = 0;
  virtual void exitSExpr(InstantParser::SExprContext *ctx) = 0;

  virtual void enterMulExpr(InstantParser::MulExprContext *ctx) = 0;
  virtual void exitMulExpr(InstantParser::MulExprContext *ctx) = 0;

  virtual void enterConstExpr(InstantParser::ConstExprContext *ctx) = 0;
  virtual void exitConstExpr(InstantParser::ConstExprContext *ctx) = 0;

  virtual void enterDivExpr(InstantParser::DivExprContext *ctx) = 0;
  virtual void exitDivExpr(InstantParser::DivExprContext *ctx) = 0;

  virtual void enterSubExpr(InstantParser::SubExprContext *ctx) = 0;
  virtual void exitSubExpr(InstantParser::SubExprContext *ctx) = 0;

  virtual void enterVarExpr(InstantParser::VarExprContext *ctx) = 0;
  virtual void exitVarExpr(InstantParser::VarExprContext *ctx) = 0;

  virtual void enterParensExpr(InstantParser::ParensExprContext *ctx) = 0;
  virtual void exitParensExpr(InstantParser::ParensExprContext *ctx) = 0;

  virtual void enterAddExpr(InstantParser::AddExprContext *ctx) = 0;
  virtual void exitAddExpr(InstantParser::AddExprContext *ctx) = 0;


};

