
// Generated from /home/martin/CLionProjects/Compilers-Operators-HELP/ShellGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ShellGrammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ShellGrammarParser.
 */
class  ShellGrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSequence(ShellGrammarParser::SequenceContext *ctx) = 0;
  virtual void exitSequence(ShellGrammarParser::SequenceContext *ctx) = 0;

  virtual void enterSeqDelim(ShellGrammarParser::SeqDelimContext *ctx) = 0;
  virtual void exitSeqDelim(ShellGrammarParser::SeqDelimContext *ctx) = 0;

  virtual void enterPipeline(ShellGrammarParser::PipelineContext *ctx) = 0;
  virtual void exitPipeline(ShellGrammarParser::PipelineContext *ctx) = 0;

  virtual void enterSimpleCommand(ShellGrammarParser::SimpleCommandContext *ctx) = 0;
  virtual void exitSimpleCommand(ShellGrammarParser::SimpleCommandContext *ctx) = 0;

  virtual void enterIoRedirect(ShellGrammarParser::IoRedirectContext *ctx) = 0;
  virtual void exitIoRedirect(ShellGrammarParser::IoRedirectContext *ctx) = 0;

  virtual void enterString(ShellGrammarParser::StringContext *ctx) = 0;
  virtual void exitString(ShellGrammarParser::StringContext *ctx) = 0;


};

