#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "tokenClass.h"
#include "glyph.h"
#include "command.h"
#include "operator.h"

const int HOSTNAME_LENGTH = 32;

int execute(char* command[]);
std::string input();
std::string getUsername();
std::string getHostname();

struct pair{
    int f, l;
}

int main() {

	std::string username = getUsername();
	std::string hostname = getHostname();

	while (true) {
		bool userError = false;
		std::string userInput;
		std::cout << username << '@' << hostname << "$ ";	
		userInput = input(); 

        int iLeft = 0, iRight = 0;
        // Index of left parentheses are right parentheses
        int level;

        for (int i = 0; i < userInput.size(); ++i) {
            if (userInput.at(i) == '(') {
                ++level;
            }
            else if (userInput.at(i) == ')') {
                --level;
            }
        }
        if (level != 0) {
           std::cout << "Error: Mismatching Parentheses" << std::endl; 



		//pass input to tokenizer
		Token fullCommand(userInput, userError);
		// Check to see if the user is stupid
		if (userError) std::cout << "Error: Syntax Error" << std::endl;
		else {
			//execute commands
			for (int i = 0; i < fullCommand.getNumCommand(); ++i) {
				if (fullCommand.getCommand(i)[0] != 0) {
					// Handle exit command
					if (strcmp(fullCommand.getCommand(i)[0], "exit") == 0) exit(EXIT_SUCCESS); 
	
                    //Handle test command
                    if (strcmp(fullCommand.getCommand(i)[0], "test") == 0) test(fullcommand.getCommand(i)); 


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
		perror("Execute: ");
		returnValue = -2;
	}
	else if (pid == 0) { //the child process
		if (execvp(command[0], command) == -1) {
			perror("Execute: ");
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
				perror("Execute: ");
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
		perror("get user name: ");
	}
	return uname;
}

std::string getHostname() {
	char hname[HOSTNAME_LENGTH];
	if (gethostname(hname, HOSTNAME_LENGTH)) {
		strcpy(hname, "unkown");
		perror("get host name: ");
	}
	return hname;
}

bool test (char* command[]) {
    struct stat info;

    if (stat(command[2], &info) == -1) {
        perror("Stat")
        return false;
    }

    if (strcmp(command[1], "-e") == 0) {
        if (S_ISREG(info.st_mode) || S_ISDIR(info.st_mode) return true; 
        else return false;
    }
    else if (strcmp(command[1], "-f") == 0) {
        return S_ISREG(info.st_mode);
    }
    else if (strcmp(command[1], "-d") == 0) {
        return S_ISDIR(info.st_mode);
    }

    return false;
}
