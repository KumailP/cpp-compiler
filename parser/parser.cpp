#include "parser.h"

using namespace std;

bool Parser::saveCursor()
{
    this->savedCursor = this->cursor;
    return true;
}

bool Parser::backtrack()
{
    // cout << "CURSOR RESET TO: " << this->savedCursor << endl;
    this->cursor = this->savedCursor;
    return true;
}

bool Parser::parse(vector<Token> tokens)
{
    this->tokens = tokens;
    this->cursor = 0;
    this->savedCursor = 0;
    if (this->start() && (unsigned)cursor == tokens.size())
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

bool Parser::term(string expected_val)
{
    // cout << peekNextToken().val << " == " << expected_val << endl;
    return getNextToken().val == expected_val;
}

bool Parser::termType(string expected_type)
{
    // cout << peekNextToken().val << ", " << peekNextToken().type << " == " << expected_type << endl;
    return getNextToken().type == expected_type;
}

bool Parser::start()
{
    return (statement());
}

bool Parser::statement()
{
    // return (saveCursor() && expression_statement() && statement()) ||
    //     (backtrack() && saveCursor() && iteration_statement() && statement()) ||
    //     (backtrack() && true);
    return (saveCursor() && expression_statement()) ||
           (backtrack() && saveCursor() && iteration_statement());
}

bool Parser::expression_statement()
{
    return (saveCursor() && declaration_statement()) ||
           (backtrack() && saveCursor() && inc_dec_statement());
}

bool Parser::condition()
{
    // i<5
    return (saveCursor() && LT_OP()) ||
           (backtrack() && saveCursor() && GT_OP()) ||
           (backtrack() && saveCursor() && EQ_OP()) ||
           (backtrack() && saveCursor() && LE_OP()) ||
           (backtrack() && saveCursor() && GE_OP()) ||
           (backtrack() && saveCursor() && NE_OP());
}

bool Parser::LT_OP()
{
    return termType("id") && term("<") && termType("num");
}

bool Parser::GT_OP()
{
    return termType("id") && term(">") && termType("num");
}

bool Parser::LE_OP()
{
    return termType("id") && term("<") && term("=") && termType("num");
}

bool Parser::GE_OP()
{
    return termType("id") && term(">") && term("=") && termType("num");
}

bool Parser::EQ_OP()
{
    return termType("id") && term("=") && term("=") && termType("num");
}

bool Parser::NE_OP()
{
    return termType("id") && term("!") && term("=") && termType("num");
}

bool Parser::iteration_statement()
{
    // while '(' expression ')' statement
    //                 | do statement while '(' expression ')' ';'
    //                 | for '(' expression_statement expression_statement ')' statement
    //                 | for '(' expression_statement expression_statement expression ')' statement
    return (saveCursor() && while_loop()) ||
           (backtrack() && saveCursor() && do_while_loop());
}

bool Parser::do_while_loop()
{
    return (term("exec") && term("{") && statement() && term("}") && term("during") && term("(") && condition() && term(")"));
}

bool Parser::while_loop()
{
    return (term("during") && term("(") && condition() && term(")") && term("{") && statement() && term("}"));
}

bool Parser::declaration_statement()
{
    if (type_specifier() && termType("id") && term("=") && termType("num")){
        return true;
    } else {
        cout << "Error in declaration statement!" << endl;
        return false;
    }
}

bool Parser::inc_dec_statement()
{
    return (saveCursor() && inc_statement()) ||
        (backtrack() && saveCursor() && dec_statement());
}

bool Parser::dec_statement()
{
    // cout << "INC STATEMENT" << endl;
    return (termType("id") && term("-") && term("-"));
}

bool Parser::inc_statement()
{
    // cout << "INC STATEMENT" << endl;
    return (termType("id") && term("+") && term("+"));
}

bool Parser::type_specifier()
{
    return termType("id");
}