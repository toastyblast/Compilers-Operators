#include <iostream>
#include <unistd.h>
#include <vector>
#include <wait.h>
#include "Pipeline.h"
#include "SimpleCommand.h"

using namespace std;

/**
 * Destructor.
 */
Pipeline::~Pipeline() {
    for (SimpleCommand *cmd : commands)
        delete cmd;
}

/**
 * Executes the commands on this pipeline.
 */
void Pipeline::execute() {
    if (commands.size() == 1) {
        //If there's only one command, just perform it.
        commands.at(0)->execute();
    } else if (commands.size() >= 2) {
        //If there's two or more however, we need to start piping!
        int pipeEnds[2];
        int fd_read = 0;
        pid_t pid;

        //Add a nullptr to the end of the list of commands, this will be the end case for our program.
        this->addCommand(nullptr);

        //Make an iterator to go through the list of commands.
        vector<SimpleCommand *>::iterator it = commands.begin();

        //As long as there is still a command in the list.
        while ((*it) != nullptr) {
            //Make a pipe.
            pipe(pipeEnds);

            //Then fork to make another process from the shell.
            if ((pid = fork()) == -1) {
                perror("Forking in pipe failed ");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                //The child process of the shell will end up here.
                if (fd_read != 0) {
                    //For all commands except the first (as then fd_read is still 0), change their stdinput to the stored read of the last pipe.
                    dup2(fd_read, 0);
                }

                //If the command after this one is not the end of the command list (which we labelled by adding a nullptr).
                if (*(it + 1) != nullptr) {
                    //Connect your stdout to the write end of the current pipe.
                    dup2(pipeEnds[1], 1);
                }

                //Close the read end of the current pipe, as you do not need it.
                close(pipeEnds[0]);

                //Now execute the command!
                (*it)->execute();
                //We shouldn't end up here at all, since the execute does an exec that should close the process.
                exit(EXIT_FAILURE);
            }

            //The parent can only get here.
            //Wait for the child to finish its command, then going to the next loop. The output of the child will be
            // buffered in the pipe until the next command starts anyways, or the loop finishes.
            waitpid(pid, nullptr, 0);

            //Close the write end of the current pipe, as we do not need it.
            close(pipeEnds[1]);

            //Save the read end of the current pipe, so that the next command can connect to it.
            fd_read = pipeEnds[0];

            //Go to the next command in the list.
            it++;
        }
    } else {
        perror("For some reason there's 0 or less commands given.");
    }
}