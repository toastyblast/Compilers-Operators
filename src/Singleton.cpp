//
// Created by toasty on 1-3-18.
//

#include "Singleton.h"

/**
 * Method to get the instance of the Singleton, and when called for the first time, also create the Singleton.
 *
 * @return Singleton& instance of the Singleton.
 */
Singleton& Singleton::getInstance() {
    //Since we have made the instance static, it is guaranteed to be destroyed.
    static Singleton instance;
    //The way this method works, and the instance being static, the singleton is only instantiated on first use.
    return instance;
}

/**
 * Method that returns the last directory that was visited, before the current one we are at.
 *
 * @return const char* which is a c_str of the last directory visited before the current one.
 */
const char* Singleton::getLastDirectory() {
    return lastDirectory;
}

/**
 * Method that can be used to set the last directory that was visited before the prior one that the user is currently at.
 *
 * @param directory const char* is a c_str that has the path of the directory the user was last in.
 */
void Singleton::setLastDirectory(const char* directory) {
    //Some sanity checks, to be sure.
    assert(directory != nullptr);
    assert(directory != "");

    lastDirectory = directory;
}

/* --- HISTORY-RELATED CODE ---------------------------------------------------------------------------------------- */

void Singleton::addCommandExecutable(Sequence * sc) {
    commandsExecutables.push_back(sc);
}

void Singleton::addCommandLine(string cmd) {
    if(cmd.find("history") == string::npos
       && cmd.find("hst") == string::npos) {
        commandsLines.push_back(cmd);
    }
}

string Singleton::getCommand(int number) {
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

void Singleton::seeHistory() {
    std::cout << " List of all the commands that were executed during this session. " << std::endl;
    std::cout << " To execute a command type hst <command number>. " << std::endl;

    for (int i = 0; i < commandsLines.size(); ++i) {
        std::cout << " [" << i << "] " << commandsLines.at(i) << std::endl;
    }
}

void Singleton::clearHistory() {
    commandsLines.clear();
}