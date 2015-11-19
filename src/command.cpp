#include "command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

Command::Command(char* d[]) {
    data = d;
}

bool Command::execute() {
    pid_t pid; //process id for child
    int status = 0;

    if ((pid = fork()) < 0) {
        perror("Execute: ");
        return false;
    }
    else if (pid == 0) { //the child process
        if (execvp(data[0], data) == -1) {
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
                return false;
                loop = false;
                perror("Execute: ");
            }

            if (WIFSIGNALED(status)) {
                return false;
            }	

            if (WIFEXITED(status)) {
                return !WEXITSTATUS(status); 
                // 0 if command succeeded, 1 if failed
            }

        } while(loop);
    }
    return false;
}
