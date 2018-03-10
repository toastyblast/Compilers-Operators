#ifndef SHELL_EXITCOMMAND_H
#define SHELL_EXITCOMMAND_H

#include <exception>

using namespace std;

/**
 * Struct class exception that can be thrown when the "exit" command is given. This will be caught by the main and
 * cause it to stop itself (and so the program).
 */
struct ExitCommand: public exception {
    ExitCommand() = default;
    virtual ~ExitCommand() throw() { /* ... */ }

    virtual const char* what() throw() {
        return "ExitCommand found... Trying normal closure of shell.\n"
                "(If you see this message, please report it. This should not be seen)";
    }
};

#endif //SHELL_EXITCOMMAND_H
