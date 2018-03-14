#include <iostream>
#include <unistd.h>
#include "Sequence.h"
#include "Pipeline.h"
#include "ExitCommand.h"
#include <sys/types.h>
#include <sys/wait.h>
void signalHandler( int signum ) {
    pid_t pid = 0;
    int status;
    waitpid(pid, &status, WNOHANG);
}
/**
 * Destructor.
 */
Sequence::~Sequence() {
    for( Pipeline *p : pipelines )
        delete p;
}

/**
 * Executes a sequence, i.e. runs all pipelines and...
 *
 * IF the ampersand (&) was used in the command - Do not wait for execution to finish
 * OR
 * Otherwise, wait until execution is done before continuing.
 */
void Sequence::execute() {
    signal(SIGCHLD, signalHandler);
    std::string skipCommand = "none";
    pid_t pid;

    for( Pipeline *p : pipelines ) {
        //If the command is build-in don't fork it.
        if(skipCommand == "none") {
            if (p->getComands().at(0)->getCommand() == "cd"
                || p->getComands().at(0)->getCommand() == "pwd"
                || p->getComands().at(0)->getCommand() == "history") {
                p->execute();
            } else if (p->findCommand("exit")){
                throw ExitCommand();
            } else {
                if (p->isAsync()) {
                    //If the command is async start it and move on.
                    if (skipCommand != "none") {
                        skipCommand = "none";
                        continue;
                    }
                    if ((pid = fork()) < 0)
                        perror("fork() error");
                    else if (pid == 0) {
                        p->execute();
                    }
                } else if (p->isContinue()) {
                    //If the command's end state needs to be checked aka has && after the command execute this.
                    if ((pid = fork()) < 0)
                        perror("fork() error");
                    else if (pid == 0) {
                        p->execute();
                    }
                    int status;
                    pid_t childPID = wait(&status);
                    int childReturnValue = WEXITSTATUS(status);
                    //If the command is OK go on if not brake the sequence execution.
                    if (childReturnValue != 0) {
                        //If a command from a "&& chain" fails, the rest of these commands should not be executed.
                        skipCommand = "&&";
                    }
                } else if (p->isStop()) {
                    //If the command's end state needs to be checked aka has || after the command execute this.
                    if ((pid = fork()) < 0)
                        perror("fork() error");
                    else if (pid == 0) {
                        p->execute();
                    }
                    int status;
                    pid_t childPID = wait(&status);
                    int childReturnValue = WEXITSTATUS(status);
                    //If the command is OK brake the sequence if not continue to try the other commands.
                    if (childReturnValue == 0) {
                        //If a command from a "|| chain" succeeds, the rest of these commands should not be executed.
                        skipCommand = "||";
                    }
                } else {
                    //If it is just a normal command execute it and wait for it to finish, then move on.
                    if ((pid = fork()) < 0)
                        perror("fork() error");
                    else if (pid == 0) {
                        p->execute();
                    }
                    wait(nullptr);
                }
            }
        } else if (skipCommand != "none") {
            if (!p->isContinue() && !p->isStop()){
                //If the command is not followed by "&&" or "||" this means that this command is the end of the operator
                //command chain. Since this is the end of the operator command chain, we can continue to execute the
                //remainder of the commands.
                skipCommand = "none";
            } else if (p->isStop() && skipCommand == "&&"){
                //This means that the chain of commands with a "&&" control operator has finished and the following
                //commands should try to be executed. In this case a new chain of commands starts with the "||" operator.
                skipCommand = "none";
            } else if (p->isContinue() && skipCommand == "||"){
                //This means that the chain of commands with a "||" control operator has finished and the following
                //commands should try to be executed. In this case a new chain of commands starts with the "&&" operator.
                skipCommand = "none";
            }
        }
    }
}
