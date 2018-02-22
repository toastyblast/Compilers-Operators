#include <iostream>
#include <unistd.h>
#include <vector>
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
//    std::cout << "FIX: You should change Pipeline::execute()" << std::endl;

    //Original code made by teachers:
//    for (SimpleCommand *cmd : commands) {
//        // FIXME: Probably need to set up some pipe here?
//
//        cmd->execute();
//    }
    // ------------

    /* --- Testing code ------------------------------------ */
//    int pipefd [2];
//
//    if (pipe(pipefd) < 0) {
//        perror("Piping fail ");
//        exit(EXIT_FAILURE);
//    }
//
//    pid_t pid = fork();
//
//    if (pid < 0) {
//        perror("Initial pipe fork error ");
//        exit(EXIT_FAILURE);
//    }
//    else if (pid == 0) {
//        //This is where the child is caught.
//        dup2(pipefd[0], 0);
//        close(pipefd[0]);
//        close(pipefd[1]);
//
//        commands.at(1)->execute();
//        exit(EXIT_SUCCESS);
//    }
//    else {
//        //Parent only gets here.
//        dup2(pipefd[1], 1);
//        close(pipefd[0]);
//        close(pipefd[1]);
//
//        commands.at(0)->execute();
//
//        //Wait for the child to finish.
//        waitpid(pid, NULL, 0);
//        exit(EXIT_SUCCESS);
//    }
//    exit(EXIT_FAILURE);
    // ----------------------------------

    if (commands.size() == 1) {
        //If there's only one command, we just execute it, as there's no need for piping.
        commands.at(0)->execute();
    } else if (commands.size() >= 2) {
        //However, as soon as two or more commands are in the vector (due to the user using the '|' character), we need
        // to start piping these together (in a chain in case of 3 or more commands).
        vector<SimpleCommand *>::iterator it;
        int input = 0;

        for (it = commands.begin(); it < (commands.end() - 1); it++) {
            //Go to all commands except the last.
            int pipefd[2];

            if (pipe(pipefd) < 0) {
                perror("Piping fail ");
            }

            //The child stays in this method while the parent leaves back to this for-loop.
            buildPipe(input, pipefd[1], (*it));

            //Close the write end of the pipe, as we don't need it. The child will be writing here.
            close(pipefd[1]);

            //Save the read end of the pipe, as the next child will have to use it.
            input = pipefd[0];
            cout << "PARENT STORED INPUT: " << input << endl;
        }

        //Increase the iterator to go to the end of the commands, as at the end of the for-loop it's at commands.end() - 1.
        it++;

        if (input != 0) {
            dup2(input, 0);
        }

        (*it)->execute();
    }
}

void Pipeline::buildPipe(int input, int output, SimpleCommand *command) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Forking command for pipe error ");
    } else if (pid == 0) {
        //The child comes here, and will do its command, as well as connecting to the right side of the pipe.
        cout << "CHILD RECEIVED INPUT: " << input << endl;
        if (input != 0) {
            //Duplicate the child's current input fd to 0, which is the standard input
            dup2(input, 0);
            //Close the old input fd of the child.
            close(input);
        }

        cout << "CHILD RECEIVED OUTPUT: " << output << endl;
        if (output != 1) {
            //Duplicate the child's current output fd to 1, which is the standard output.
            dup2(output, 1);
            //Close the old output fd of the child.
            close(output);
        }

        //And finally perform the command the child has to do.
        command->execute();
    }
}