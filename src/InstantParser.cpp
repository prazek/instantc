
// Generated from Instant.g4 by ANTLR 4.7


#include "InstantListener.h"
#include "InstantVisitor.h"

#include "InstantParser.h"


using namespace antlrcpp;
using namespace antlr4;

InstantParser::InstantParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

InstantParser::~InstantParser() {
  delete _interpreter;
}

std::string InstantParser::getGrammarFileName() const {
  return "Instant.g4";
}

const std::vector<std::string>& InstantParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& InstantParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

InstantParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InstantParser::StmtContext *> InstantParser::ProgramContext::stmt() {
  return getRuleContexts<InstantParser::StmtContext>();
}

InstantParser::StmtContext* InstantParser::ProgramContext::stmt(size_t i) {
  return getRuleContext<InstantParser::StmtContext>(i);
}


size_t InstantParser::ProgramContext::getRuleIndex() const {
  return InstantParser::RuleProgram;
}

void InstantParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void InstantParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any InstantParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

InstantParser::ProgramContext* InstantParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, InstantParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(6);
    stmt();
    setState(11);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(7);
        match(InstantParser::T__0);
        setState(8);
        stmt(); 
      }
      setState(13);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
    setState(15);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InstantParser::T__0) {
      setState(14);
      match(InstantParser::T__0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

InstantParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InstantParser::StmtContext::getRuleIndex() const {
  return InstantParser::RuleStmt;
}

void InstantParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SExprContext ------------------------------------------------------------------

InstantParser::ExprContext* InstantParser::SExprContext::expr() {
  return getRuleContext<InstantParser::ExprContext>(0);
}

InstantParser::SExprContext::SExprContext(StmtContext *ctx) { copyFrom(ctx); }

void InstantParser::SExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSExpr(this);
}
void InstantParser::SExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSExpr(this);
}

antlrcpp::Any InstantParser::SExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitSExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignExprContext ------------------------------------------------------------------

tree::TerminalNode* InstantParser::AssignExprContext::IDENT() {
  return getToken(InstantParser::IDENT, 0);
}

InstantParser::ExprContext* InstantParser::AssignExprContext::expr() {
  return getRuleContext<InstantParser::ExprContext>(0);
}

InstantParser::AssignExprContext::AssignExprContext(StmtContext *ctx) { copyFrom(ctx); }

void InstantParser::AssignExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignExpr(this);
}
void InstantParser::AssignExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignExpr(this);
}

antlrcpp::Any InstantParser::AssignExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitAssignExpr(this);
  else
    return visitor->visitChildren(this);
}
InstantParser::StmtContext* InstantParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 2, InstantParser::RuleStmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(21);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<InstantParser::AssignExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(17);
      match(InstantParser::IDENT);
      setState(18);
      match(InstantParser::T__1);
      setState(19);
      expr(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<InstantParser::SExprContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(20);
      expr(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

InstantParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InstantParser::ExprContext::getRuleIndex() const {
  return InstantParser::RuleExpr;
}

void InstantParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulExprContext ------------------------------------------------------------------

std::vector<InstantParser::ExprContext *> InstantParser::MulExprContext::expr() {
  return getRuleContexts<InstantParser::ExprContext>();
}

InstantParser::ExprContext* InstantParser::MulExprContext::expr(size_t i) {
  return getRuleContext<InstantParser::ExprContext>(i);
}

InstantParser::MulExprContext::MulExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::MulExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExpr(this);
}
void InstantParser::MulExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExpr(this);
}

antlrcpp::Any InstantParser::MulExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitMulExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstExprContext ------------------------------------------------------------------

tree::TerminalNode* InstantParser::ConstExprContext::INT() {
  return getToken(InstantParser::INT, 0);
}

InstantParser::ConstExprContext::ConstExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::ConstExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstExpr(this);
}
void InstantParser::ConstExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstExpr(this);
}

antlrcpp::Any InstantParser::ConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitConstExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DivExprContext ------------------------------------------------------------------

std::vector<InstantParser::ExprContext *> InstantParser::DivExprContext::expr() {
  return getRuleContexts<InstantParser::ExprContext>();
}

InstantParser::ExprContext* InstantParser::DivExprContext::expr(size_t i) {
  return getRuleContext<InstantParser::ExprContext>(i);
}

InstantParser::DivExprContext::DivExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::DivExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDivExpr(this);
}
void InstantParser::DivExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDivExpr(this);
}

antlrcpp::Any InstantParser::DivExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitDivExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubExprContext ------------------------------------------------------------------

std::vector<InstantParser::ExprContext *> InstantParser::SubExprContext::expr() {
  return getRuleContexts<InstantParser::ExprContext>();
}

InstantParser::ExprContext* InstantParser::SubExprContext::expr(size_t i) {
  return getRuleContext<InstantParser::ExprContext>(i);
}

InstantParser::SubExprContext::SubExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::SubExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubExpr(this);
}
void InstantParser::SubExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubExpr(this);
}

antlrcpp::Any InstantParser::SubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitSubExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarExprContext ------------------------------------------------------------------

tree::TerminalNode* InstantParser::VarExprContext::IDENT() {
  return getToken(InstantParser::IDENT, 0);
}

InstantParser::VarExprContext::VarExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::VarExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarExpr(this);
}
void InstantParser::VarExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarExpr(this);
}

antlrcpp::Any InstantParser::VarExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitVarExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParensExprContext ------------------------------------------------------------------

InstantParser::ExprContext* InstantParser::ParensExprContext::expr() {
  return getRuleContext<InstantParser::ExprContext>(0);
}

InstantParser::ParensExprContext::ParensExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::ParensExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParensExpr(this);
}
void InstantParser::ParensExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParensExpr(this);
}

antlrcpp::Any InstantParser::ParensExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitParensExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddExprContext ------------------------------------------------------------------

std::vector<InstantParser::ExprContext *> InstantParser::AddExprContext::expr() {
  return getRuleContexts<InstantParser::ExprContext>();
}

InstantParser::ExprContext* InstantParser::AddExprContext::expr(size_t i) {
  return getRuleContext<InstantParser::ExprContext>(i);
}

InstantParser::AddExprContext::AddExprContext(ExprContext *ctx) { copyFrom(ctx); }

void InstantParser::AddExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpr(this);
}
void InstantParser::AddExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InstantListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpr(this);
}

antlrcpp::Any InstantParser::AddExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<InstantVisitor*>(visitor))
    return parserVisitor->visitAddExpr(this);
  else
    return visitor->visitChildren(this);
}

InstantParser::ExprContext* InstantParser::expr() {
   return expr(0);
}

InstantParser::ExprContext* InstantParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  InstantParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  InstantParser::ExprContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, InstantParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(30);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case InstantParser::IDENT: {
        _localctx = _tracker.createInstance<VarExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(24);
        match(InstantParser::IDENT);
        break;
      }

      case InstantParser::INT: {
        _localctx = _tracker.createInstance<ConstExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(25);
        match(InstantParser::INT);
        break;
      }

      case InstantParser::T__6: {
        _localctx = _tracker.createInstance<ParensExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(26);
        match(InstantParser::T__6);
        setState(27);
        expr(0);
        setState(28);
        match(InstantParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(46);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(44);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<DivExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(32);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(33);
          match(InstantParser::T__2);
          setState(34);
          expr(8);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MulExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(35);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(36);
          match(InstantParser::T__3);
          setState(37);
          expr(7);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<SubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(38);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(39);
          match(InstantParser::T__4);
          setState(40);
          expr(6);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AddExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(41);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(42);
          match(InstantParser::T__5);
          setState(43);
          expr(4);
          break;
        }

        } 
      }
      setState(48);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool InstantParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool InstantParser::exprSempred(ExprContext */*_localctx*/, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> InstantParser::_decisionToDFA;
atn::PredictionContextCache InstantParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN InstantParser::_atn;
std::vector<uint16_t> InstantParser::_serializedATN;

std::vector<std::string> InstantParser::_ruleNames = {
  "program", "stmt", "expr"
};

std::vector<std::string> InstantParser::_literalNames = {
  "", "';'", "'='", "'/'", "'*'", "'-'", "'+'", "'('", "')'"
};

std::vector<std::string> InstantParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "INT", "IDENT", "WS"
};

dfa::Vocabulary InstantParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> InstantParser::_tokenNames;

InstantParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xd, 0x34, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0xc, 0xa, 0x2, 0xc, 0x2, 
    0xe, 0x2, 0xf, 0xb, 0x2, 0x3, 0x2, 0x5, 0x2, 0x12, 0xa, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x18, 0xa, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x21, 
    0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 
    0x2f, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x32, 0xb, 0x4, 0x3, 0x4, 0x2, 0x3, 
    0x6, 0x5, 0x2, 0x4, 0x6, 0x2, 0x2, 0x2, 0x39, 0x2, 0x8, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x17, 0x3, 0x2, 0x2, 0x2, 0x6, 0x20, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0xd, 0x5, 0x4, 0x3, 0x2, 0x9, 0xa, 0x7, 0x3, 0x2, 0x2, 0xa, 0xc, 0x5, 
    0x4, 0x3, 0x2, 0xb, 0x9, 0x3, 0x2, 0x2, 0x2, 0xc, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0xd, 0xb, 0x3, 0x2, 0x2, 0x2, 0xd, 0xe, 0x3, 0x2, 0x2, 0x2, 0xe, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0xf, 0xd, 0x3, 0x2, 0x2, 0x2, 0x10, 0x12, 
    0x7, 0x3, 0x2, 0x2, 0x11, 0x10, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x3, 0x3, 0x2, 0x2, 0x2, 0x13, 0x14, 0x7, 0xc, 
    0x2, 0x2, 0x14, 0x15, 0x7, 0x4, 0x2, 0x2, 0x15, 0x18, 0x5, 0x6, 0x4, 
    0x2, 0x16, 0x18, 0x5, 0x6, 0x4, 0x2, 0x17, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x17, 0x16, 0x3, 0x2, 0x2, 0x2, 0x18, 0x5, 0x3, 0x2, 0x2, 0x2, 0x19, 
    0x1a, 0x8, 0x4, 0x1, 0x2, 0x1a, 0x21, 0x7, 0xc, 0x2, 0x2, 0x1b, 0x21, 
    0x7, 0xb, 0x2, 0x2, 0x1c, 0x1d, 0x7, 0x9, 0x2, 0x2, 0x1d, 0x1e, 0x5, 
    0x6, 0x4, 0x2, 0x1e, 0x1f, 0x7, 0xa, 0x2, 0x2, 0x1f, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x20, 0x19, 0x3, 0x2, 0x2, 0x2, 0x20, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x20, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x21, 0x30, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0x23, 0xc, 0x9, 0x2, 0x2, 0x23, 0x24, 0x7, 0x5, 0x2, 0x2, 0x24, 
    0x2f, 0x5, 0x6, 0x4, 0xa, 0x25, 0x26, 0xc, 0x8, 0x2, 0x2, 0x26, 0x27, 
    0x7, 0x6, 0x2, 0x2, 0x27, 0x2f, 0x5, 0x6, 0x4, 0x9, 0x28, 0x29, 0xc, 
    0x7, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x7, 0x2, 0x2, 0x2a, 0x2f, 0x5, 0x6, 
    0x4, 0x8, 0x2b, 0x2c, 0xc, 0x6, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x8, 0x2, 
    0x2, 0x2d, 0x2f, 0x5, 0x6, 0x4, 0x6, 0x2e, 0x22, 0x3, 0x2, 0x2, 0x2, 
    0x2e, 0x25, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x2b, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x32, 0x3, 0x2, 0x2, 0x2, 0x30, 0x2e, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 0x31, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x8, 0xd, 0x11, 0x17, 
    0x20, 0x2e, 0x30, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

InstantParser::Initializer InstantParser::_init;
