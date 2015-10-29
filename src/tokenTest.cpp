#include <vector>
#include <iostream>
#include "tokenClass.h"
int main() {
    Token a("ls -a || pwd && echo -e hello  ; hi");
    // std::cout << a.getCommand(0).size() << std::endl;  
    //std::cout << a.getCommand(1)[0] << std::endl;
    //std::cout << a.g.size() << std::endl;
    for(int i = 0; i < a.getNumCommand(); ++i) {
//    	std::cout << a.getVCommand(i).size() << std::endl;
	for(int j = 0; j < a.getVCommand(i).size(); ++j) {
	  //  std::cout << i << ' ' << j << std::endl;
	   std::cout << a.getCommand(i)[j] << std::endl;
	}
	std::cout << a.getConnector(i) << std::endl;  
    }
    //a.getCommand(0, b);
//    std::couts << a.getCommand(0).at(0) << std::endl;
}
