
// Generated from /home/martin/CLionProjects/Compilers-Operators-gr/ShellGrammar.g4 by ANTLR 4.7


#include "ShellGrammarLexer.h"


using namespace antlr4;


ShellGrammarLexer::ShellGrammarLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ShellGrammarLexer::~ShellGrammarLexer() {
  delete _interpreter;
}

std::string ShellGrammarLexer::getGrammarFileName() const {
  return "ShellGrammar.g4";
}

const std::vector<std::string>& ShellGrammarLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& ShellGrammarLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& ShellGrammarLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& ShellGrammarLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& ShellGrammarLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> ShellGrammarLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& ShellGrammarLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> ShellGrammarLexer::_decisionToDFA;
atn::PredictionContextCache ShellGrammarLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ShellGrammarLexer::_atn;
std::vector<uint16_t> ShellGrammarLexer::_serializedATN;

std::vector<std::string> ShellGrammarLexer::_ruleNames = {
  u8"SEMICOLON", u8"AMPERSAND", u8"X2AMPERSANDCO", u8"X2LINECO", u8"PIPE", 
  u8"Digit", u8"REDIRECTFD", u8"REDIRECT", u8"EscapedQuote", u8"QUOTEDSTRING", 
  u8"EscapedSpace", u8"StringCharacter", u8"STRING", u8"WS"
};

std::vector<std::string> ShellGrammarLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> ShellGrammarLexer::_modeNames = {
  u8"DEFAULT_MODE"
};

std::vector<std::string> ShellGrammarLexer::_literalNames = {
  "", u8"';'", u8"'&'", u8"'&&'", u8"'||'", u8"'|'"
};

std::vector<std::string> ShellGrammarLexer::_symbolicNames = {
  "", u8"SEMICOLON", u8"AMPERSAND", u8"X2AMPERSANDCO", u8"X2LINECO", u8"PIPE", 
  u8"REDIRECTFD", u8"REDIRECT", u8"QUOTEDSTRING", u8"STRING", u8"WS"
};

dfa::Vocabulary ShellGrammarLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ShellGrammarLexer::_tokenNames;

ShellGrammarLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
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
    0x2, 0xc, 0x62, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 
    0x4, 0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
    0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 
    0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 
    0xe, 0x4, 0xf, 0x9, 0xf, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x5, 0x8, 0x2f, 0xa, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x35, 0xa, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x9, 0x5, 0x9, 0x3b, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x41, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x49, 0xa, 0xb, 0xc, 0xb, 
    0xe, 0xb, 0x4c, 0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x55, 0xa, 0xd, 0x3, 0xe, 0x6, 0xe, 
    0x58, 0xa, 0xe, 0xd, 0xe, 0xe, 0xe, 0x59, 0x3, 0xf, 0x6, 0xf, 0x5d, 
    0xa, 0xf, 0xd, 0xf, 0xe, 0xf, 0x5e, 0x3, 0xf, 0x3, 0xf, 0x3, 0x4a, 0x2, 
    0x10, 0x3, 0x3, 0x5, 0x4, 0x7, 0x5, 0x9, 0x6, 0xb, 0x7, 0xd, 0x2, 0xf, 
    0x8, 0x11, 0x9, 0x13, 0x2, 0x15, 0xa, 0x17, 0x2, 0x19, 0x2, 0x1b, 0xb, 
    0x1d, 0xc, 0x3, 0x2, 0x6, 0x3, 0x2, 0x32, 0x3b, 0x4, 0x2, 0xc, 0xc, 
    0xf, 0xf, 0x8, 0x2, 0xb, 0xc, 0xf, 0xf, 0x22, 0x22, 0x24, 0x24, 0x28, 
    0x28, 0x7e, 0x7e, 0x5, 0x2, 0xb, 0xc, 0xf, 0xf, 0x22, 0x22, 0x2, 0x68, 
    0x2, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x2, 0x9, 0x3, 0x2, 0x2, 0x2, 0x2, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x2, 0xf, 0x3, 0x2, 0x2, 0x2, 0x2, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x2, 0x15, 0x3, 0x2, 0x2, 0x2, 0x2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x2, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0x3, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x5, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x7, 0x23, 0x3, 0x2, 0x2, 0x2, 0x9, 0x26, 0x3, 0x2, 0x2, 0x2, 
    0xb, 0x29, 0x3, 0x2, 0x2, 0x2, 0xd, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xf, 0x2e, 
    0x3, 0x2, 0x2, 0x2, 0x11, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x13, 0x42, 0x3, 
    0x2, 0x2, 0x2, 0x15, 0x45, 0x3, 0x2, 0x2, 0x2, 0x17, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x19, 0x54, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x57, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x3d, 0x2, 0x2, 
    0x20, 0x4, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x7, 0x28, 0x2, 0x2, 0x22, 
    0x6, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x28, 0x2, 0x2, 0x24, 0x25, 
    0x7, 0x28, 0x2, 0x2, 0x25, 0x8, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x7, 
    0x7e, 0x2, 0x2, 0x27, 0x28, 0x7, 0x7e, 0x2, 0x2, 0x28, 0xa, 0x3, 0x2, 
    0x2, 0x2, 0x29, 0x2a, 0x7, 0x7e, 0x2, 0x2, 0x2a, 0xc, 0x3, 0x2, 0x2, 
    0x2, 0x2b, 0x2c, 0x9, 0x2, 0x2, 0x2, 0x2c, 0xe, 0x3, 0x2, 0x2, 0x2, 
    0x2d, 0x2f, 0x5, 0xd, 0x7, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x34, 0x3, 0x2, 0x2, 0x2, 0x30, 0x35, 
    0x7, 0x40, 0x2, 0x2, 0x31, 0x32, 0x7, 0x40, 0x2, 0x2, 0x32, 0x35, 0x7, 
    0x40, 0x2, 0x2, 0x33, 0x35, 0x7, 0x3e, 0x2, 0x2, 0x34, 0x30, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x31, 0x3, 0x2, 0x2, 0x2, 0x34, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x35, 0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0x28, 0x2, 0x2, 
    0x37, 0x38, 0x5, 0xd, 0x7, 0x2, 0x38, 0x10, 0x3, 0x2, 0x2, 0x2, 0x39, 
    0x3b, 0x5, 0xd, 0x7, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0x3b, 0x40, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x41, 0x7, 
    0x40, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x40, 0x2, 0x2, 0x3e, 0x41, 0x7, 0x40, 
    0x2, 0x2, 0x3f, 0x41, 0x7, 0x3e, 0x2, 0x2, 0x40, 0x3c, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x40, 0x3f, 0x3, 0x2, 0x2, 0x2, 
    0x41, 0x12, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0x5e, 0x2, 0x2, 0x43, 
    0x44, 0x7, 0x24, 0x2, 0x2, 0x44, 0x14, 0x3, 0x2, 0x2, 0x2, 0x45, 0x4a, 
    0x7, 0x24, 0x2, 0x2, 0x46, 0x49, 0x5, 0x13, 0xa, 0x2, 0x47, 0x49, 0xa, 
    0x3, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x47, 0x3, 0x2, 
    0x2, 0x2, 0x49, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4d, 0x3, 0x2, 0x2, 0x2, 
    0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0x24, 0x2, 0x2, 0x4e, 
    0x16, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x5e, 0x2, 0x2, 0x50, 0x51, 
    0x7, 0x22, 0x2, 0x2, 0x51, 0x18, 0x3, 0x2, 0x2, 0x2, 0x52, 0x55, 0xa, 
    0x4, 0x2, 0x2, 0x53, 0x55, 0x5, 0x17, 0xc, 0x2, 0x54, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x54, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x1a, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x58, 0x5, 0x19, 0xd, 0x2, 0x57, 0x56, 0x3, 0x2, 0x2, 0x2, 
    0x58, 0x59, 0x3, 0x2, 0x2, 0x2, 0x59, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 
    0x5a, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5d, 
    0x9, 0x5, 0x2, 0x2, 0x5c, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x3, 
    0x2, 0x2, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x5f, 0x60, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x8, 0xf, 0x2, 
    0x2, 0x61, 0x1e, 0x3, 0x2, 0x2, 0x2, 0xc, 0x2, 0x2e, 0x34, 0x3a, 0x40, 
    0x48, 0x4a, 0x54, 0x59, 0x5e, 0x3, 0x8, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ShellGrammarLexer::Initializer ShellGrammarLexer::_init;
