//
// Created by martin on 01/03/18.
//

#ifndef SHELL_HISTORY_H
#define SHELL_HISTORY_H

#include <vector>
#include <Sequence.h>
#include <string>

class History{
private:
    std::vector<Sequence*> commandsExecutables;
    History() = default;
    std::vector<std::string> commandsLines;
public:
    static History *getHistory();
    void addCommandExecutable(Sequence*);
    void addCommandLine(std::string);
    void seeHistory();
    void clearHistory();
    std::string getCommand(int);
};
#endif //SHELL_HISTORY_H
