all: new

compiler: 
	g++ -std=c++11 -Wall -g -o compiler main.cpp lexical_analyzer/token.cpp lexical_analyzer/lexer.cpp

new: clean compiler run

run: compiler
	./compiler

clean:
	rm -f compiler.exe
