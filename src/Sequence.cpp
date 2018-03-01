#include <iostream>
#include <unistd.h>
#include "Sequence.h"
#include "Pipeline.h"
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
	std::cout << "FIXME: You should change Sequence::execute()" << std::endl;
	signal(SIGCHLD, signalHandler);
	pid_t pid;

	for( Pipeline *p : pipelines ) {
        //If the command is build-in don't fork it.
		if (p->getComands().at(0)->getCommand() == "cd"
                || p->getComands().at(0)->getCommand() == "pwd"){
            p->execute();
        } else {
            if(p->isAsync()){
                //If the command is async start it and move on.
                if ((pid = fork()) < 0)
                    perror("fork() error");
                else if (pid == 0) {
                    p->execute();
                }
            } else if(p->isWait()){
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
                if(childReturnValue != 0){
                    break;
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
	}
}
