#include <iostream>
#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>
#include <unistd.h>
#include "../gen/ShellGrammarLexer.h"
#include "../gen/ShellGrammarParser.h"
#include "CommandVisitor.h"
#include "Sequence.h"
#include "Singleton.h"
#include "ExitCommand.h"
#include <pwd.h>

class ErrorListener : public antlr4::BaseErrorListener {
    bool seenError;

public:
    ErrorListener()
            : antlr4::BaseErrorListener(), seenError(false) {}

    bool hasSeenError() const { return seenError; }

    void reset() { seenError = false; }

    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                     size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
        std::cerr << "ERROR in input - line " << line << ":" << charPositionInLine << " " << msg << std::endl;
        seenError = true;
    }
};

int main() {
    //Get the user's details.
    struct passwd *pw = getpwuid(getuid());
    //Get the user's home dir path.
    const char *directory = pw->pw_dir;
    //Change the home dir.
    chdir(directory);

    static const char *PROMPT = "-> ";
    try {
        while (true) {
            // Print the current directory and the prompt
            std::cout << ::get_current_dir_name() << " " << PROMPT;
            std::flush(std::cout);

            // Read a complete line
            std::string line;
            std::getline(std::cin, line);
            if (line.substr(0, 3) == "hst" && line.size() > 3) {
                std::istringstream iss(line);
                std::string cmd;
                iss >> cmd;
                std::string number;
                iss >> number;
                if (!isdigit(number.at(0))) {
                    std::cerr << "Invalid number!" << std::endl;
                    continue;
                }
                line = Singleton::getInstance().getCommand(std::stoi(number));
                if (line == "bad") {
                    continue;
                }
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
            if (!errorListener2.hasSeenError()) {
                // Take apart the line entered into sequences, pipelines and commands
                CommandVisitor visitor2;
                Sequence *sequence2 = visitor2.visit(parseTree2);

                // Execute sequence
                // Now these execute() methods are were you have to add your code...
                Singleton::getInstance().addCommandLine(line);
                sequence2->execute();

                // Cleanup
                delete sequence2;
            }
        }
    } catch (ExitCommand) {
        cout << "Exiting program now..." << endl;
    }

    cout << "Goodbye!" << endl;
    return 0;
}
