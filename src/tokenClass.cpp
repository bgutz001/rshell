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
   
//    std::cout << "-------input--------\n" << str << std::endl; 
    error = false;

    // utitlize stringstream to tokenize
    std::istringstream iss(str);
    unsigned i = 0;
    unsigned j = 0;

    i = std::count(str.begin(), str.end(), ')'); 
    j = std::count(str.begin(), str.end(), '('); 
    if( i - j ) error = true;
    
    if(str.find("((") != std::string::npos) error = true;
    if(str.find("))") != std::string::npos) error = true; 
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
    bool isBracket = false;
    bool immediate = false;
    bool removal = false;
    //while loop. this tkenizes then handles connectors
    while(std::getline(iss, command.at(j).at(i), ' ') && !error) {
	if(command.at(j).at(i) == "" || command.at(j).at(i) == " ") removal = true;
	else if((command.at(j).at(i) == "||" || command.at(j).at(i) == "&&" || command.at(j).at(i) == ";" || command.at(j).at(i).back() == ';') && !isBracket) {
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
	    if(isBracket) {
		if(command.at(j).at(i).at(command.at(j).at(i).size() - 1) == ']') {
		    if(command.at(j).at(i) == "]") removal = true;
		    else command.at(j).at(i).pop_back();
		    isBracket = false;
		    
		}
		if(immediate) {
		    if(command.at(j).at(i).at(0) != '-') {
			command.at(j).push_back(command.at(j).at(i));
			command.at(j).at(i) = "-e";
			i++;
		    }
		    immediate = false;
		}
	    }
		    
	    if(command.at(j).at(i).at(0) == '[') {
		isBracket = true;
		immediate = true;
		if(command.at(j).at(i) == "[") {
		    command.at(j).at(i) = "test";
		}
		else {
		    command.at(j).push_back(command.at(j).at(i));
		    command.at(j).at(i) = "test";
		    i++;
		    command.at(j).at(i).erase(command.at(j).at(i).begin());
		    if(command.at(j).at(i).at(0) != '-') {
			command.at(j).push_back(command.at(j).at(i));
			command.at(j).at(i) = "-e";
			i++;
			immediate = false;
		    }
		}
		if(command.at(j).at(i).at(command.at(j).at(i).size() - 1) == ']') {
		    if(command.at(j).at(i) == "]") {
			removal = true;
		    }
		    else command.at(j).at(i).pop_back();
		    isBracket = false;
		    immediate = false;
		}
	    }
	    
	    if(command.at(j).at(i).at(0) == '(') {
		if(command.at(j).at(i).at(command.at(j).at(i).size() - 1) == ')');
		else {
		    std::string temp;
		    std::string tracker;
		    std::getline(iss, temp, ')');
		    int x = std::count(temp.begin(), temp.end(), '('); 
		    temp += ")";
		    tracker = temp;
		    int y = std::count(command.at(j).at(i).begin(), command.at(j).at(i).end(), '(');
//		    std::cout << "\nX: " << x << "\nY: " << y << std::endl;
		    if(iss.eof()) error = true;
		    if(x + y  > std::count(tracker.begin(), tracker.end(), ')') && !iss.eof()) {
			while(x + y  > std::count(tracker.begin(), tracker.end(), ')')) {
			    std::getline(iss,temp, ')');
			    temp += ")";
			    tracker += temp;
//			    std::cout << "-------tracker----------\n" << tracker << std::endl;
			    x = std::count(tracker.begin(), tracker.end(), '(') + y; 
			    if(iss.eof()) {
				//error = true;
				x = -1;
			    } 
			}
			tracker.pop_back();
		    }
		    command.at(j).at(i) += " ";
		    command.at(j).at(i) += tracker;
		    x = std::count(str.begin(), str.end(), ')'); 
		    y = std::count(str.begin(), str.end(), '('); 
		    if( x - y ) error = true;
//		    std::cout << "--------result---------\n" << command.at(j).at(i) << std::endl;
//		    std::cout << "-------error-flag------\n" << error << std::endl;
		}
	    }
    	}
	
	if(removal) {
	    command.at(j).pop_back();
	    if(command.at(j).size() == 0) command.at(j).push_back("");
//	    std::cout << command.at(j).at(i) << std::endl;
	    i--;
	    removal = false;
	}
	
	i++; 
	
	//resizes second vector
	if(i == command.at(j).size()) {
	   command.at(j).push_back("");
	}
    }
  
    if(isBracket) error = true;		
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
