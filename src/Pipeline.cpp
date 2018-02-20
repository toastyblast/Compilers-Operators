#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "Pipeline.h"
#include "SimpleCommand.h"

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
//    std::cout << "FIXME: You should change Pipeline::execute()" << std::endl;

    pid_t parentID = fork();

    if (parentID < 0) {
        perror("Initial pipe fork error ");
    } else if (parentID == 0) {
        int in, fd [2];

        in = 0;

        for (SimpleCommand *command : commands) {
            pipe (fd);

            buildPipe(in, fd [1], command);

            close (fd [1]);

            in = fd [0];
        }

        if (in != 0) {
            dup2(in, 0);
        }

        commands.at(commands.size() - 1)->execute();
    }

    wait(nullptr);

    //Original code made by teachers:
//    for (SimpleCommand *cmd : commands) {
//        // FIXME: Probably need to set up some pipe here?
//
//        cmd->execute();
//    }
}

int Pipeline::buildPipe(int in, int out, SimpleCommand *command) {
    pid_t pid;

    if ((pid = fork ()) == 0) {
        if (in != 0) {
            dup2 (in, 0);
            close (in);
        }

        if (out != 1) {
            dup2 (out, 1);
            close (out);
        }

        return command->execute();
    }

    return pid;
}