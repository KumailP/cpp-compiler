all: new

compiler: 
	g++ -std=c++11 -Wall -g -o compiler main.cpp lexical_analyzer/token.cpp lexical_analyzer/lexer.cpp parser/parser.cpp

new: clean compiler run

run: compiler
	clear && ./compiler

clean:
	rm -f compiler.exe
