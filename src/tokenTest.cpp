#include <vector>
#include <iostream>
#include "tokenClass.h"
int main() {
    Token a("ls -a || pwd && echo -e help");
   // std::cout << a.getCommand(0).size() << std::endl;  
    for(int i = 0; i < a.getNumCommand(); i++) {
	for(int j = 0; j < a.getCommand(i).size(); j++) {
	    std::cout << a.getCommand(i).at(j) << std::endl;
	}  
    }

//    std::couts << a.getCommand(0).at(0) << std::endl;
}
