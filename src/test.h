#ifndef TEST_H
#define TEST_H

class Test : Glyph {
    private:
        char* data[];
    public:
        Test(char* d[]);
        bool execute();
};

#endif
