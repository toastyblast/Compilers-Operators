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
//    std::cout << "FIX: You should change Pipeline::execute()" << std::endl;

    //Original code made by teachers:
//    for (SimpleCommand *cmd : commands) {
//        // FIXME: Probably need to set up some pipe here?
//
//        cmd->execute();
//    }

    int pipefd [2];

    if (pipe(pipefd) < 0) {
        perror("Piping fail ");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Initial pipe fork error ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        //This is where the child is caught.
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        close(pipefd[1]);

        commands.at(1)->execute();
        exit(EXIT_SUCCESS);
    }
    else {
        //Parent only gets here.
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);

        commands.at(0)->execute();

        //Wait for the child to finish.
        waitpid(pid, NULL, 0);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);

    /* --- Other, testing code ----------------------------- */
//    int input = 0;
//    int fd [2];
//    char buffer[80];
//
//    /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
//    for (SimpleCommand *command : commands) {
//        pipe(fd);
//
//        /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
//        buildPipe(input, fd[1], command);
//
//        /* No need for the write end of the pipe, the child will write here.  */
//        close(fd[1]);
//
//        /* Keep the read end of the pipe, the next child will read from there.  */
//        input = fd[0];
//    }
//
//    /* Last stage of the pipeline - set stdin be the read end of the previous pipe
//       and output to the original file descriptor 1. */
//    if (input != 0) {
//        dup2(input, 0);
//    }
//
//    /* Execute the last stage with the current process. */
//    commands.at(commands.size() - 1)->execute();
}

int Pipeline::buildPipe(int in, int out, SimpleCommand *command) {
    pid_t pid;

    if ((pid = fork ()) == 0) {
        if (in != 0) {
            dup2(in, 0);
            close(in);
        }

        if (out != 1) {
            dup2(out, 1);
            close(out);
        }

        command->execute();
    }

    return pid;
}