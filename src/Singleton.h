#ifndef SHELL_SINGLETON_H
#define SHELL_SINGLETON_H

#include <antlr4-runtime.h>
#include "Sequence.h"

using namespace std;

/**
 * Singleton class that can be used to store data that needs to stay persistent over the whole shell's lifespan.
 */
class Singleton {
public:
    //Inline method to get the instance of the singleton.
    static Singleton& getInstance();

private:
    //Constructor, starts empty, will be filled with data throughout the shell's lifespan.
    Singleton() = default;
    ~Singleton() = default;

    const char* lastDirectory;

    std::vector<Sequence*> commandsExecutables;
    std::vector<std::string> commandsLines;

public:
    //Prevent the copy constructor and operator copy constructor from being usable.
    Singleton(Singleton const &) = delete;
    Singleton& operator = (Singleton const &) = delete;

    const char* getLastDirectory();
    void setLastDirectory(const char*);

    void addCommandExecutable(Sequence*);
    void addCommandLine(string);
    void seeHistory();
    void clearHistory();
    string getCommand(int);
};


#endif //SHELL_SINGLETON_H
