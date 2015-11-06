all: 
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ./src/main.cpp ./src/tokenClass.cpp -std=c++11 -o ./bin/rshell

rshell:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ./src/main.cpp ./src/tokenClass.cpp -std=c++11 -o ./bin/rshell
