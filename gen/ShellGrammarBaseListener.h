
// Generated from /home/martin/CLionProjects/Compilers-Operators-HELP/ShellGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ShellGrammarListener.h"


/**
 * This class provides an empty implementation of ShellGrammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ShellGrammarBaseListener : public ShellGrammarListener {
public:

  virtual void enterSequence(ShellGrammarParser::SequenceContext * /*ctx*/) override { }
  virtual void exitSequence(ShellGrammarParser::SequenceContext * /*ctx*/) override { }

  virtual void enterSeqDelim(ShellGrammarParser::SeqDelimContext * /*ctx*/) override { }
  virtual void exitSeqDelim(ShellGrammarParser::SeqDelimContext * /*ctx*/) override { }

  virtual void enterPipeline(ShellGrammarParser::PipelineContext * /*ctx*/) override { }
  virtual void exitPipeline(ShellGrammarParser::PipelineContext * /*ctx*/) override { }

  virtual void enterSimpleCommand(ShellGrammarParser::SimpleCommandContext * /*ctx*/) override { }
  virtual void exitSimpleCommand(ShellGrammarParser::SimpleCommandContext * /*ctx*/) override { }

  virtual void enterIoRedirect(ShellGrammarParser::IoRedirectContext * /*ctx*/) override { }
  virtual void exitIoRedirect(ShellGrammarParser::IoRedirectContext * /*ctx*/) override { }

  virtual void enterString(ShellGrammarParser::StringContext * /*ctx*/) override { }
  virtual void exitString(ShellGrammarParser::StringContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

