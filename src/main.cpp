#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <algorithm>
#include "tokenClass.h"

const int HOSTNAME_LENGTH = 32;

bool execute(char* command[]);
bool process(std::string c);
std::string input();
std::string getUsername();
std::string getHostname();
bool test(char* command[]);

struct pair {
    int begin, end, depth;
    pair(int b, int e, int d) {
        begin = b;
        end = e;
        depth = d;
    }
    bool operator<(const pair& rhs) {
        return this->depth < rhs.depth;
    }
};


int main() {

	std::string username = getUsername();
	std::string hostname = getHostname();

    while (true) {
        std::string userInput;
        std::cout << username << '@' << hostname << "$ ";	
        userInput = input(); 
        process(userInput);
    }

    return 0;
}

bool process(std::string c) {
    bool result = true;
    bool userError = false;
    bool par = false; // Are there parentheses around a command
    std::string secondc;

    if (int i = c.find('(') != std::string::npos) {
        par = true;
        secondc = c.substr(i, c.size() - i);
        c.erase(i, c.size() - i);
        std::cout << "Fixed string: " << c << std::endl;

    }

    //pass input to tokenizer
    Token fullCommand(c, userError);

    // Check to see if the user is stupid
    if (userError) {
        std::cout << "Error: Syntax Error" << std::endl;
        return false;
    }

    //execute commands
    for (int i = 0; i < fullCommand.getNumCommand(); ++i) {
        if (fullCommand.getCommand(i)[0] != 0) {
            // Handle exit command
            if (strcmp(fullCommand.getCommand(i)[0], "exit") == 0) exit(EXIT_SUCCESS); 

            //Handle test command
            //if (strcmp(fullCommand.getCommand(i)[0], "test") == 0) test(fullcommand.getCommand(i)); 


            if (i != fullCommand.getNumCommand() - 1) {
                bool status = execute(fullCommand.getCommand(i));

                // Handle || connector
                // If first command succeeds then don't execute
                // second command
                if (status) {
                    while (fullCommand.getConnector(i) == "ORTRUE"
                            && i < fullCommand.getNumCommand()) {
                        ++i;
                    }
                }		

                // Handle && connector
                // If first command fails then don't execute
                // second command
                else if (!status) {
                    while (fullCommand.getConnector(i) == "ANDTRUE"
                            && i < fullCommand.getNumCommand()) {
                        ++i;
                    }
                }					

            }
            // Execute last command
            else {
                result = execute(fullCommand.getCommand(i));
                if (par) {
                    if (result && fullCommand.getConnector(i) == "ORTRUE") {
                        result = process(secondc);
                    }
                    else if (!result && fullCommand.getConnector(i) == "ANDTRUE") {
                        result = process(secondc);
                    }
                }
            }
        }
    }
    return result;
}



//parameter: command list you want to execute, last char* should be null
//return: returns true if command succeded 
//Description: executes a program in /bin/sh/ on a child process
bool execute(char* command[]) {

    pid_t pid; //process id for child
    int status = 0;

    if ((pid = fork()) < 0) {
        perror("Execute: ");
        return false;
    }
    else if (pid == 0) { //the child process
        if (execvp(command[0], command) == -1) {
            perror("Execute: ");
            exit(EXIT_FAILURE);
        }
        bool loop;
        do {
            int p = waitpid(pid, &status, 0);

            loop = (p != pid);
            //handles errors and exit statuses 
            if (p == -1) { 
                return false; 
                loop = false;
                perror("Execute: ");
            }
            if (WIFSIGNALED(status)) { 
                return false; 
            }	
            if (WIFEXITED(status)) {
                return !WEXITSTATUS(status); // 0 if command succeeded, 1 if failed
            }

        } while(loop);
    }
    return false;
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
        perror("Stat");
        return false;
    }

    if (strcmp(command[1], "-e") == 0) {
        if (S_ISREG(info.st_mode) || S_ISDIR(info.st_mode)) return true; 
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
