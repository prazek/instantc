
// Generated from Instant.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "InstantParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by InstantParser.
 */
class  InstantVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by InstantParser.
   */
    virtual antlrcpp::Any visitProgram(InstantParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitAssignExpr(InstantParser::AssignExprContext *context) = 0;

    virtual antlrcpp::Any visitSExpr(InstantParser::SExprContext *context) = 0;

    virtual antlrcpp::Any visitMulExpr(InstantParser::MulExprContext *context) = 0;

    virtual antlrcpp::Any visitConstExpr(InstantParser::ConstExprContext *context) = 0;

    virtual antlrcpp::Any visitDivExpr(InstantParser::DivExprContext *context) = 0;

    virtual antlrcpp::Any visitSubExpr(InstantParser::SubExprContext *context) = 0;

    virtual antlrcpp::Any visitVarExpr(InstantParser::VarExprContext *context) = 0;

    virtual antlrcpp::Any visitParensExpr(InstantParser::ParensExprContext *context) = 0;

    virtual antlrcpp::Any visitAddExpr(InstantParser::AddExprContext *context) = 0;
};

