#include "tokenClass.h"
Token::Token()
{ } 

Token::~Token() {
    if(c_command != 0 ) {
 	delete[] *c_command;
	delete[] c_command;
	c_command = 0;
    }
} 

Token::Token(std::string str){
    //deletes comments. Might need to change
    if(std::string::npos != str.find('#')) {
	str.erase(str.find('#'));
    } 
    
    /*HANDLE QUOTES
      HERE. TBD
    */

    // utitlize stringstream to tokenize
    std::istringstream iss(str);
    int i = 0;
    int j = 0;
    
    //setup command vec size
    command.resize(1,std::vector<std::string>(1, ""));

    //while loop. this tokenizes then handles connectors
    while(std::getline(iss, command.at(j).at(i), ' ')) {
		if(command.at(j).at(i) == "||" || command.at(j).at(i) == "&&" || command.at(j).at(i) == ";") {
			if(command.at(j).at(i) == "||") connector.push_back("ORTRUE");
			if(command.at(j).at(i) == "&&") connector.push_back("ANDTRUE");
			if(command.at(j).at(i) == ";")  connector.push_back("CONTINUE");
	    
			//deletes connecotr in the vector
			command.at(j).pop_back();
			j++;
	    
			//resizes first vector
			if(j == command.size()) command.resize(j + 1, std::vector<std::string>(1));

			//will be incremented in after if escape
			i = -1;
		}
		i++; 

		//resizes second vector
		if(i == command.at(j).size()) {
			command.at(j).push_back("");
		}
    } 
    
	//deletes hanging vector
    command.at(j).pop_back();
    connector.push_back("STOP");
    
    //sets up the c_command to be copied
    c_command = 0;
}

char** Token::getCommand(int x) {
    //deletes the old c_command
    char** deleter = c_command;
    
	c_command = new char*[command.at(x).size() + 1];
 
	for( int i = 0; i < command.at(x).size(); i++) {
		c_command[i] = new char[command.at(x).at(i).length() + 1];
		strcpy(c_command[i], command.at(x).at(i).c_str());
    }
   
	//adds null pointer
	c_command[command.at(x).size()] = 0;

	//removing old array    
    if(deleter == 0) { return c_command;}
    delete[] *deleter;
//	delete[] *deleter + 1;
	delete[] deleter;
    deleter = 0;
    return c_command;
} 

std::vector<std::string> Token::getVCommand(int x) {
    return command.at(x);
}
int Token::getNumCommand() {
    return command.size();
}

std::string Token::getConnector(int x) {
    return connector.at(x);
}
