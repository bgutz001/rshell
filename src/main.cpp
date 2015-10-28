#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

const int HOSTNAME_LENGTH = 16;

int execute(char* command[]);
std::string input();
std::string getUsername();
std::string getHostname();

int main() {
	/*
	char* temp[] = {"pwd", 0};
	execute(temp);
	char* temp2[] = {"exit", 0};
	execute(temp2);
	*/

	std::string username = getUsername();
	std::string hostname = getHostname();

	while (true) {
		std::string userInput;
		std::cout << username << '@' << hostname << "$ ";	
		userInput = input(); 
	}
    return 0;
}

int execute(char* command[]) {
	// Handle 'exit'
	if (command[0] == "exit") exit(EXIT_SUCCESS);
	pid_t pid;
	int status = 0;
	if ((pid = fork()) < 0) {
		std::cout << "Failed to create child proccess" << std::endl;
		perror(0);
		return -1;
	}
	if (pid == 0) { //child
		if (execvp(command[0], command) == -1) {
			std::cout << "Command failed" << std::endl;
			perror(0);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else { // parent
		
			while(waitpid(pid, &status, 0) != pid);
	
		return 0;
	}
	return 0;
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
