#ifndef TOKENCLASS_H
#define TOKENCLASS_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
class Token {
    public:
	//DO NOT CALL THIS ONE
	Token();
	//string is the string to be tokenized
	Token(std::string);
	//the int is the number of the command accessed. 
	std::vector<std::string> getCommand(int);
	//gets the number of commands
	int getNumCommand();
	//gets the corresponding connector value
	std::string getConnector(int);
    private:
    	std::vector<std::vector<std::string> > command;
	std::vector<std::string> connector;
};

#endif
