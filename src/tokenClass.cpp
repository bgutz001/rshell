#include "tokenClass.h"
#include <algorithm>
Token::Token()
{ } 

Token::~Token() {
    if(c_command != 0 ) {
        for(int i = 0; i < old_size; i++) delete[] c_command[i];
        delete[] c_command;
        c_command = 0;
    }
} 

Token::Token(std::string str, bool &error){
    //deletes comments. Might need to change
    if(std::string::npos != str.find('#')) {
        str.erase(str.find('#'));
    }
    
    error = false;

    // utitlize stringstream to tokenize
    std::istringstream iss(str);
    unsigned i = 0;
    unsigned j = 0;

    i = std::count(str.begin(), str.end(), ')'); 
    j = std::count(str.begin(), str.end(), '('); 
    if( i - j ) error = true;
     
    i = std::count(str.begin(), str.end(), ']'); 
    j = std::count(str.begin(), str.end(), '['); 
    if( i - j ) error = true;
    
    i = std::count(str.begin(), str.end(), '\"'); 
    if((i % 2) ) error = true;
    

    i = 0;
    j = 0;
    
    //setup command vec size
    command.resize(1,std::vector<std::string>(1, ""));
    bool double_connectors = false;    

    //while loop. this tokenizes then handles connectors
    while(std::getline(iss, command.at(j).at(i), ' ')) {
	if((command.at(j).at(i) == "||" || command.at(j).at(i) == "&&" || command.at(j).at(i) == ";" || command.at(j).at(i).back() == ';')) {
	    if(command.at(j).at(i) == "||") connector.push_back("ORTRUE");
	    if(command.at(j).at(i) == "&&") connector.push_back("ANDTRUE");
	    if(command.at(j).at(i) == ";")  connector.push_back("CONTINUE");
	    if(command.at(j).at(i).back() == ';') {
		connector.push_back("CONTINUE");
	    }
	    else command.at(j).pop_back();
	    if(double_connectors) {
		//syntax error
		error = true;
	    }
			
	    double_connectors = true;
	    j++;
			
	    //resizes first vector
	    if(j == command.size()) command.resize(j + 1, std::vector<std::string>(1));
	    //will be incremented in after if escape
	    i = -1;
	}
	else {
	    ////////////////////////////////////////////////////////////////////
	    /////													////////////////
	    ////		replace Array with command.at(i).at(j)		//////////////
	    ///														////////////////
	    ///////////////////////////////////////////////////////////////
	    double_connectors = false;
	    if(command.at(j).at(i).at(0) == '\"') {
	    	//std::cout << "Found it" << std::endl;
	    	command.at(j).at(i).erase(command.at(j).at(i).begin());
		if(command.at(j).at(i).at(command.at(j).at(i).size() - 1) == '\"') {
		    command.at(j).at(i).pop_back();
		}
		else {
		    std::string temp;
		    std::getline(iss, temp, '\"');
		    command.at(j).at(i) += " ";
		    command.at(j).at(i) += temp;
		}
	    }			
			
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

    //if(multi_word || bracket) error = true;
   //sets up the c_command to be copied
    c_command = 0;
    old_size = 0;
}

char** Token::getCommand(int x) {
    //deletes the old c_command
    char** deleter = c_command;
    int new_size = old_size;
    old_size = 0;
    c_command = new char*[command.at(x).size() + 1];

    for(unsigned i = 0; i < command.at(x).size(); i++) {
        old_size++;
        c_command[i] = new char[command.at(x).at(i).length() + 1];
        copy(command.at(x).at(i).begin(), command.at(x).at(i).end(), c_command[i]);
        c_command[i][command.at(x).at(i).size()] = '\0';
    }

    //adds null pointer
    c_command[command.at(x).size()] = 0;

    //removing old array    
    if(deleter == 0) { return c_command;} 
    for(int i = 0; i < new_size; i++) delete[] deleter[i];
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
