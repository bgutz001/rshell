#include "tokenClass.h"
Token::Token()
{ } 

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
	//connector handling
	if(command.at(j).at(i) == "||" || command.at(j).at(i) == "&&" || 
	    command.at(j).at(i) == ";") {
		if(command.at(j).at(i) == "||") connector.push_back("ORTRUE");
		if(command.at(j).at(i) == "&&") connector.push_back("ANDTRUE");
		else connector.push_back("CONTINUE");
	    
	    //deletes connecotr in the vector
	    command.at(j).resize(i - 1);
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
}

char** Token::getCommand(int x, char ** &c_command) {
    //Not entirely sure about this top line, but ensures c_command is empty to begin with
    //delete [] c_command;
    c_command = new char*[command.at(x).size()];
    for( int i = 0; i < command.at(x).size(); i++) {
	c_command[i] = new char[command.at(x).at(i).length() + 1];
	strcpy(c_command[i], command.at(x).at(i).c_str());
    }
//    c_command = temp;
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
