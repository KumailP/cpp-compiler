#include "parser.h"

using namespace std;

bool Parser::saveCursor()
{
    this->savedCursor = this->cursor;
    return true;
}

bool Parser::backtrack()
{
    this->cursor = this->savedCursor;
    return true;
}

bool Parser::parse(vector<Token> tokens)
{
    this->tokens = tokens;
    this->cursor = 0;
    this->savedCursor = 0;
    if (this->start() && cursor == tokens.size())
    {
        cout << "Parse successful" << endl;
        return true;
    }
    else
    {
        cout << "Parse failure" << endl;
        return false;
    }
}

Token Parser::getNextToken()
{
    Token nextToken = this->tokens[cursor];
    this->cursor++;
    return nextToken;
}

Token Parser::peekNextToken()
{
    Token nextToken = this->tokens[cursor];
    return nextToken;
}

bool Parser::term(string expected_type)
{
    cout << peekNextToken().val << ", " << peekNextToken().type << " == " << expected_type << endl;
    return getNextToken().type == expected_type;
}

bool Parser::start()
{
    return (this->statement() && this->term("symb"));
}

bool Parser::statement()
{
    return (this->saveCursor() && this->declaration_statement()) || 
    (this->backtrack() && this->saveCursor() && this->inc_statement());
}

bool Parser::declaration_statement()
{
    return (this->type_specifier() && this->term("id") && this->term("symb") && this->term("num"));
}

bool Parser::inc_statement()
{
    cout << "INC" << endl;
    return (this->term("id") && this->term("symb") && this->term("symb"));
}

bool Parser::type_specifier()
{
    return this->term("id");
}