#include "tokenClass.h"
Token::Token()
{ } 

Token::~Token() {
    if(c_command != 0 ) {
    	//int x2 = sizeof(c_command) / sizeof(*c_command);
	//for(int i = 0; i <= x2; i++) {
	  //  delete [] c_command[i];
	//}
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
//	std::cout << command.at(j).at(i) << std::endl;
	//connector handling
	if(command.at(j).at(i) == "||" || command.at(j).at(i) == "&&" || 
	    command.at(j).at(i) == ";") {
		if(command.at(j).at(i) == "||") connector.push_back("ORTRUE");
		if(command.at(j).at(i) == "&&") connector.push_back("ANDTRUE");
		if(command.at(j).at(i) == ";")  connector.push_back("CONTINUE");
	    
	    //deletes connecotr in the vector
	    command.at(j).resize(i);
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
    //Not entirely sure about this top line, but ensures c_command is empty to begin with
    char** deleter = c_command;
    c_command = new char*[command.at(x).size()];
    for( int i = 0; i < command.at(x).size(); i++) {
	c_command[i] = new char[command.at(x).at(i).length() + 1];
	strcpy(c_command[i], command.at(x).at(i).c_str());
    }
    //removing old array
    int x2 = sizeof(deleter) / sizeof(*deleter);
    //int y = sizeof(*deleter) / sizeof(**deleter);
    if(deleter == 0) { return c_command;}
    //for(int i = 0; i <= x2; i++) {
//	delete [] deleter[i];
  //  }
    delete[] deleter;
    deleter = 0;
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
