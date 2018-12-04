#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include "../lexical_analyzer/token.h"

using namespace std;

class Parser
{
  public:
    int cursor = 0;
    int savedCursor = 0;
    vector<Token> tokens; // list of tokens

    bool parse(vector<Token> tokens);
    bool saveCursor();
    bool backtrack();
    Token getNextToken();
    Token peekNextToken();
    bool term(string expected_type);
    bool start();
    bool statement();
    bool declaration_statement();
    bool inc_statement();
    bool type_specifier();

};

#endif