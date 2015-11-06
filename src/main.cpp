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
		bool userError = false;
		std::string userInput;
		std::cout << username << '@' << hostname << "$ ";	
		userInput = input(); 


		//pass input to tokenizer
		Token fullCommand(userInput, userError);
		if (userError) std::cout << "Error: Syntax Error" << std::endl;
		else {
			//execute commands
			for (int i = 0; i < fullCommand.getNumCommand(); ++i) {
				// Handle exit command
				if (fullCommand.getCommand(i) != 0 &&
					strcmp(fullCommand.getCommand(i)[0], "exit") == 0) exit(EXIT_SUCCESS); 
	
				if (i != fullCommand.getNumCommand() - 1) {
					int status = execute(fullCommand.getCommand(i));

					// Handle || connector
					// If first command succeeds then don't execute
					// second command
					if (status == 0) {
						while (fullCommand.getConnector(i) == "ORTRUE"
							&& i < fullCommand.getNumCommand()) {
							++i;
						}
					}		
				
					// Handle && connector
					// If first command fails then don't execute
					// second command
					else if (status != 0) {
						while (fullCommand.getConnector(i) == "ANDTRUE"
							&& i < fullCommand.getNumCommand()) {
							++i;
						}
					}					
				}
				// Execute last command
				else {
					execute(fullCommand.getCommand(i));
				}
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
