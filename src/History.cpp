//
// Created by martin on 01/03/18.
//

#include <iostream>
#include "History.h"

History* History::getHistory() {
    static History history;
    return &history;
}

void History::addCommandExecutable(Sequence * sc) {
    commandsExecutables.push_back(sc);
}

void History::addCommandLine(std::string cmd) {
    if(cmd.find("history") == std::string::npos
            && cmd.find("hst") == std::string::npos){
        commandsLines.push_back(cmd);
    }
}

std::string History::getCommand(int number) {
    if (!commandsLines.empty()){
        if (number >= 0 && number < commandsLines.size()) {
            return commandsLines.at(number);
        } else {
            std::cerr << "Invalid number!" << std::endl;
            return "bad";
        }
    } else {
        std::cerr << "No commands have been executed yet." << std::endl;
        return "bad";
    }

}

void History::seeHistory() {
    std::cout << " List of all the commands that were executed during this session. " << std::endl;
    std::cout << " To execute a command type hst <command number>. " << std::endl;
    for (int i = 0; i < commandsLines.size(); ++i) {
        std::cout << " [" << i << "] " << commandsLines.at(i) << std::endl;
    }
}

void History::clearHistory() {
    commandsLines.clear();
}