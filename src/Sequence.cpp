#include <iostream>
#include <unistd.h>
#include "Sequence.h"
#include "Pipeline.h"

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

	for( Pipeline *p : pipelines ) {
		// FIXME: More code needed?
		p->execute();
	}
}
