#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "tokenClass.h"

const int HOSTNAME_LENGTH = 16;

int execute(char* command[]);
std::string input();
std::string getUsername();
std::string getHostname();

int main() {

	std::string username = getUsername();
	std::string hostname = getHostname();

	while (true) {
		std::string userInput;
		std::cout << username << '@' << hostname << "$ ";	
		userInput = input(); 

		//handle exit
		if (userInput == "exit") exit(EXIT_SUCCESS);

		//pass input to tokenizer
		Token fullCommand(userInput);

		//execute commands
		for (int i = 0; i < fullCommand.getNumCommand(); ++i) {
			if (i != fullCommand.getNumCommand() - 1) {
				// Handle || connector
				// If first command succeeds then don't execute
				// second command
				if ((execute(fullCommand.getCommand(i)) == 0) &&
					fullCommand.getConnector(i) == "ORTRUE") {
					// Jump to ; connector	
					while (fullCommand.getConnector(i) != "CONTINUE") {
						// Break if no there are no more connectors
						if (fullCommand.getConnector(i) == "STOP") break;	
						++i;
					} 
				}		
				
				// Handle && connector
			
			
			}
			// Execute last command
			else {
				execute(fullCommand.getCommand(i));
			}
		}
	}
    return 0;
}

//parameter: command list you want to execute, last char* should be null
//return: returns 1 if command failed
//return: returns -1 if process was killed
//return: returns -2 if there was a system error
//return: returns 0 if command succeeded
//Description: executes a program in /bin/sh/ on a child process
int execute(char* command[]) {

	pid_t pid; //process id for child
	int returnValue = 0;
	int status = 0;

	if ((pid = fork()) < 0) {
		perror(0);
		returnValue = -2;
	}
	else if (pid == 0) { //the child process
		if (execvp(command[0], command) == -1) {
			perror(0);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else { //the parent process
		//wait until the child process has exited
		bool loop;
		do {
			int p = waitpid(pid, &status, 0);

			loop = (p != pid);

			//handles errors and exit statuses
			if (p == -1) {
				returnValue = -2;
				loop = false;
				perror(0);
			}
			
			if (WIFSIGNALED(status)) {
				returnValue = -1;
			}	

			if (WIFEXITED(status)) {
				returnValue = WEXITSTATUS(status); // 0 if command succeeded, 1 if failed
			}

		} while(loop);
	}

	return returnValue;
}

std::string input() {
	std::string temp;
	std::getline(std::cin, temp);
	return temp;
}

std::string getUsername() {
	char* uname;
	if (!(uname = getlogin())) {
		uname = (char*) "unkown";
		perror(0);
	}
	return uname;
}

std::string getHostname() {
	char hname[HOSTNAME_LENGTH];
	if (gethostname(hname, HOSTNAME_LENGTH)) {
		strcpy(hname, "unkown");
		perror(0);
	}
	return hname;
}
