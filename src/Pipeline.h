#ifndef SHELL_PIPELINE_H
#define SHELL_PIPELINE_H

#include <vector>
#include "SimpleCommand.h"

/**
 * A pipeline, i.e. a set of simple commands of which the output of each previous
 * command is fed as the input to the next.
 * Note that you can have a pipeline with just a single command in which case it
 * is simply executed as is.
 */
class Pipeline {
	private:
		std::vector<SimpleCommand *> commands; //< The commands to execute
		bool async;                            //< True if this the sequence does not need to wait for the
		                                       //  pipeline to finish.
	    bool continueOnSuccess;
	    bool stopOnSuccess;
        bool wait;
	public:
		Pipeline()
				: commands()
				, async(false)
		, continueOnSuccess(false)
		, stopOnSuccess(false)
		{}

		~Pipeline();

		bool isAsync() const    { return async; }
        bool isWait() const { return wait;}
		void setAsync( bool b ) { async = b; }

	    bool isStop() const { return stopOnSuccess;}
	    bool isContinue() const { return continueOnSuccess;}

	    void setStop(bool b){stopOnSuccess = b;}
	    void setContinue(bool b){continueOnSuccess = b;}
		void addCommand( SimpleCommand *cmd ) { commands.push_back(cmd); }
        std::vector<SimpleCommand *> getComands() { return commands;}
		int const findCommand(std::string) const;

		void execute();
};


#endif //SHELL_PIPELINE_H
