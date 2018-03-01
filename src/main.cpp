#include <iostream>
#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>
#include "../gen/ShellGrammarLexer.h"
#include "../gen/ShellGrammarParser.h"
#include "CommandVisitor.h"
#include "Sequence.h"

class ErrorListener : public antlr4::BaseErrorListener {
	bool seenError;

public:
	ErrorListener()
		: antlr4::BaseErrorListener()
		, seenError(false)
	{}

	bool hasSeenError() const { return seenError; }
	void reset()              { seenError = false; }

	void syntaxError( antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
					  size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e ) override {
		std::cerr << "ERROR in input - line " << line << ":" << charPositionInLine << " " << msg << std::endl;
		seenError = true;
	}
};

int main() {
    //PLEASE NOTE: I tried putting this into a method, since it's duplicate code from a bit further on. However, this
    // would result in a code 11 SIGSEGV. I couldn't find anything on this error code in conjunction to what I was
    // doing, so sadly I have to leave this duplicate code in, or the shell won't work.

    //Do a command first, which is the "cd ~" command. This is so that we have the user start in their home directory.
    // Create an error listener. This will be called when an error occured.
    ErrorListener errorListener;

    // Create parser and lexer for line
    // The lexer combines characters into meaningful tokens
    // The parser then uses these tokens to deduce meaning of the line
    antlr4::ANTLRInputStream inputStream("cd ~");
    ShellGrammarLexer lexer(&inputStream);
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    antlr4::CommonTokenStream tokens(&lexer);
    ShellGrammarParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    // Actually parse the line
    antlr4::tree::ParseTree *parseTree = parser.sequence();

    //Create a visitor that will create a sequence out of each seperate command in the parse tree we made.
    CommandVisitor visitor;
    Sequence *sequence = visitor.visit(parseTree);

    // Execute the sequence of commands.
    sequence->execute();

    // Cleanup
    delete sequence;

	static const char *PROMPT = "-> ";
	while( true ) {
		// Print a prompt
		std::cout << PROMPT;
		std::flush(std::cout);

		// Read a complete line
		std::string line;
		std::getline(std::cin, line);

		// Check if the user typed 'exit'.
		// Now this is a bit of a hack, since the nice way to do this is actually
		// just check for 'exit' in the SimpleCommand-class.
		// TODO: You are encouraged to remove this hack and handle things 'the nice way'.
		if( line == "exit" ) {
            break;
        }

		// Create an error listener. This will be called when an error occured.
		ErrorListener errorListener2;

		// Create parser and lexer for line
		// The lexer combines characters into meaningful tokens
		// The parser then uses these tokens to deduce meaning of the line
		antlr4::ANTLRInputStream inputStream2(line);
		ShellGrammarLexer lexer2(&inputStream2);
		lexer2.removeErrorListeners();
		lexer2.addErrorListener(&errorListener2);
		antlr4::CommonTokenStream tokens2(&lexer2);
		ShellGrammarParser parser2(&tokens2);
		parser2.removeErrorListeners();
		parser2.addErrorListener(&errorListener2);

		// Actually parse the line
		antlr4::tree::ParseTree *parseTree2 = parser2.sequence();

		// Did ANTLR report an error?
		if( !errorListener2.hasSeenError() ) {
			// Take apart the line entered into sequences, pipelines and commands
			CommandVisitor visitor2;
			Sequence *sequence2 = visitor2.visit(parseTree2);

			// Execute sequence
			// Now these execute() methods are were you have to add your code...
			sequence2->execute();

			// Cleanup
			delete sequence2;
		}
	}

	return 0;
}