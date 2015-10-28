#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int execute(char* command[]);
std::string input();

int main() {
	char* temp[] = {"ls", "-a", 0};
	execute(temp);
	char* temp2[] = {"exit", 0};
	execute(temp2);

	while (true) {
		
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
