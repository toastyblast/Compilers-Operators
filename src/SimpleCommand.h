#ifndef SHELL_SIMPLECOMMAND_H
#define SHELL_SIMPLECOMMAND_H

#include <vector>
#include <string>
#include "IORedirect.h"

/**
 * A command that is part of a pipeline.
 * Commands can be builtin (like cd or exit) or programs that should be executed.
 *
 * All streams (stdout, stdin, stderr) of the command can be redirected to either
 * another stream or a file. For example, input can be taken from a file instead
 * of the keyboard, or errors from stderr can be written to a file instead of the
 * console.
 * IORedirections are always executed in order, from left to right.
 */
class SimpleCommand {
	private:
		std::string              command;
		std::vector<std::string> arguments;
		std::vector<IORedirect>  redirects;

	public:
		SimpleCommand( std::string const &cmd )
				: command(cmd)
		{}

		void addArgument( std::string const &s ) { arguments.push_back(s); }
        std::string getCommand()const { return command;}
		void addIORedirect( int fd, IORedirect::Type t, std::string const &s ) {
			redirects.emplace_back(fd, t, s);
		}

		void execute();

	private:
		void pwdPerform();
	    void chdirPerform();

	    void ioredirectPerfrom();
	    void cmdPerform();

		/* --- LEGACY CODE ----------------------------------------------------------------------------------------- */
		//Left in upon Paul de Groot's request.
		void dolsoChecks();
		void oldlsPerform(const char *);
		void oldallsPerform(const char *);
		int isRegularFile(const char *path);
};


#endif //SHELL_SIMPLECOMMAND_H
