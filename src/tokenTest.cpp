#include <vector>
#include <iostream>
#include "tokenClass.h"
int main() {
    Token a("ls -a || pwd && echo -e help");
   // std::cout << a.getCommand(0).size() << std::endl;  
    char** b;
    for(int i = 0; i < a.getNumCommand(); i++) {
	for(int j = 0; j < a.getVCommand(i).size(); j++) {
	    a.getCommand[i,b];
	    std::cout << b << std::endl;
	}  
    }
    //a.getCommand(0, b);
//    std::couts << a.getCommand(0).at(0) << std::endl;
}
