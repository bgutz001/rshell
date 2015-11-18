#ifndef COMMAND_H
#define COMMAND_H
#include "glyph.h"

class Command : Glyph {
    private:
    char* data[];

    public:
    Command(char* d[]);
    bool execute();

}

#endif
