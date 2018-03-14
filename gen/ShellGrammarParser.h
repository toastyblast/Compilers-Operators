
// Generated from /home/martin/CLionProjects/Compilers-Operators-HELP/ShellGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  ShellGrammarParser : public antlr4::Parser {
public:
  enum {
    SEMICOLON = 1, AMPERSAND = 2, X2AMPERSANDCO = 3, X2LINECO = 4, PIPE = 5, 
    REDIRECTFD = 6, REDIRECT = 7, QUOTEDSTRING = 8, STRING = 9, WS = 10
  };

  enum {
    RuleSequence = 0, RuleSeqDelim = 1, RulePipeline = 2, RuleSimpleCommand = 3, 
    RuleIoRedirect = 4, RuleString = 5
  };

  ShellGrammarParser(antlr4::TokenStream *input);
  ~ShellGrammarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class SequenceContext;
  class SeqDelimContext;
  class PipelineContext;
  class SimpleCommandContext;
  class IoRedirectContext;
  class StringContext; 

  class  SequenceContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *lastAmpersand = nullptr;;
    SequenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PipelineContext *> pipeline();
    PipelineContext* pipeline(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<SeqDelimContext *> seqDelim();
    SeqDelimContext* seqDelim(size_t i);
    antlr4::tree::TerminalNode *AMPERSAND();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SequenceContext* sequence();

  class  SeqDelimContext : public antlr4::ParserRuleContext {
  public:
    SeqDelimContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AMPERSAND();
    antlr4::tree::TerminalNode *X2AMPERSANDCO();
    antlr4::tree::TerminalNode *X2LINECO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SeqDelimContext* seqDelim();

  class  PipelineContext : public antlr4::ParserRuleContext {
  public:
    PipelineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimpleCommandContext *> simpleCommand();
    SimpleCommandContext* simpleCommand(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PipelineContext* pipeline();

  class  SimpleCommandContext : public antlr4::ParserRuleContext {
  public:
    SimpleCommandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StringContext *> string();
    StringContext* string(size_t i);
    std::vector<IoRedirectContext *> ioRedirect();
    IoRedirectContext* ioRedirect(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleCommandContext* simpleCommand();

  class  IoRedirectContext : public antlr4::ParserRuleContext {
  public:
    IoRedirectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REDIRECT();
    StringContext *string();
    antlr4::tree::TerminalNode *REDIRECTFD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IoRedirectContext* ioRedirect();

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *QUOTEDSTRING();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringContext* string();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

