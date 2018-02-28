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
		if(p->isAsync()){
			if ((pid = fork()) < 0)
				perror("fork() error");
			else if (pid == 0) {
				p->execute();
				exit(1);
			}
		} else {
			p->execute();
		}

	}
}
