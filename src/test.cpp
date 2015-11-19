#include <sys/stat.h>

Test::Test(char* d[]) {
    data = d;
}

bool Test::execute() {
    struct stat info;

    if (stat(data[2], &info) == -1) {
        perror("Stat");
        return false;
    }

    if (strcmp(data[1], "-e") == 0) {
        if (S_ISREG(info.st_mode) || S_ISDIR(info.st_mode))
            return true; 
        else return false;
    }
    else if (strcmp(data[1], "-f") == 0) {
        return S_ISREG(info.st_mode);
    }
    else if (strcmp(data[1], "-d") == 0) {
        return S_ISDIR(info.st_mode);
    }

    return false;
}
