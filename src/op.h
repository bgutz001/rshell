#ifndef OP_H
#define OP_H
#include "glyph.h"
#include <string>

class Op : Glyph {
    private:
        Glyph* left, right;
        std::string type;
    public:
        Op(Glyph* l, Glyph* r);
        bool execute();
        ~Op();
};

#endif
