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
    bool term(string expected_val);
    bool termType(string expected_type);
    bool start();
    bool statement();
    bool expression_statement();
    bool iteration_statement();
    bool declaration_statement();
    bool assignment_statement();
    bool expression();
    bool inc_dec_statement();
    bool inc_statement();
    bool dec_statement();
    bool condition();
    bool LE_OP();
    bool GE_OP();
    bool LT_OP();
    bool GT_OP();
    bool EQ_OP();
    bool NE_OP();
    bool while_loop();
    bool do_while_loop();
    bool type_specifier();

};

#endif