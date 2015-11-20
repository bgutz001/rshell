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

int execute(char* command[]);
bool process(std::string c);
std::string input();
std::string getUsername();
std::string getHostname();
bool test(char* command[]);


int main() {

    std::string username = getUsername();
    std::string hostname = getHostname();
    std::string userInput;

    while (true) {
        std::cout << username << '@' << hostname << "$ ";	
        std::getline(std::cin, userInput);
        process(userInput);
    }

    return 0;
}

bool process(std::string c) {
    bool result;
    bool userError = false;


    //pass input to tokenizer
    Token fullCommand(c, userError);

    // Check to see if the user is stupid
    if (userError) {
        std::cout << "Error: Syntax Error" << std::endl;
        return false;
    }

    //execute commands
    for (int i = 0; i < fullCommand.getNumCommand(); ++i) {
        result = false;
        if (fullCommand.getCommand(i)[0] != 0) {
            std::string com(fullCommand.getCommand(i)[0]);
            std::cout << "command is: " << com << std::endl;

            // Handle exit command
            if (com == "exit") exit(EXIT_SUCCESS); 

            //Handle test command
            //else if (strcmp(fullCommand.getCommand(i)[0], "test") == 0) test(fullcommand.getCommand(i)); 

            // Check if command is in parentheses
            else if (com.find('(') != std::string::npos) {
                result = process(com.substr(1, com.size() - 2));
            }
            else { 
                result = (execute(fullCommand.getCommand(i)) == 0);
            }

            // Check Connectors

            // Handle || connector
            // If first command succeeds then don't execute
            // second command
            if (result) {
                while (i < fullCommand.getNumCommand() &&
                        fullCommand.getConnector(i) == "ORTRUE") {
                    ++i;
                }
            }		

            // Handle && connector
            // If first command fails then don't execute
            // second command
            else if (!result) {
                while (i < fullCommand.getNumCommand() &&
                        fullCommand.getConnector(i) == "ANDTRUE") {
                    ++i;
                }
            }					
        }
    }
    return result;
}



//parameter: command list you want to execute, last char* should be null
//return: returns true if command succeded 
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
        if (execvp(command[0],
                    command) == -1) {
            perror("Execute");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        //the parent process
        //wait until the child process has exited
        bool loop;
        do
        {
            int p = waitpid(pid, &status, 0); 
            loop = (p != pid);

            //handles errors and exit statuses
            if (p == -1) {
                returnValue = -2;
                loop = false;
                perror("Execute");
            }
            if (WIFSIGNALED(status)) {
                returnValue = -1;
            }       

            if (WIFEXITED(status)) {
                returnValue = WEXITSTATUS(status);
            }

        }
        while(loop);
    }
    return returnValue;
}

std::string input() {
    std::string temp;
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
