#ifndef TOKENCLASS_H
#define TOKENCLASS_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

//remove later
#include <cstdlib>
class Token {
    public:
	//DO NOT CALL THIS ONE
	Token();
	~Token();
	//string is the string to be tokenized
	Token(std::string);
	//the int is the number of the command accessed. 
	char** getCommand(int);
	//returns Vector Command
	std::vector<std::string> getVCommand(int);
	//gets the number of commands
	int getNumCommand();
	//gets the corresponding connector value
	std::string getConnector(int);
    private:
	int old_size;
    	std::vector<std::vector<std::string> > command;
//	char** c_command;
//	std::vector<char **> test;
	char** c_command;
	std::vector<std::string> connector;
};

#endif
