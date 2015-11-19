#include "glyph.h"
#include "op.h"
#include <string>

Op::Op(Glyph* l, Glyph* r, std::string t) {
    left = l;
    right = r;
    type = t;
}

bool Op::execute() {
    if (type == "AND") {
        if (left->execute()) right->execute();
    }
    else if (type == "OR") {
        if (!left->execute()) right->execute();
    }
    else if (type == "CONTINUE") {
        left->execute();
        right->execute();
    }
}

Op::~Op() {
    delete left;
    delete right;
}
