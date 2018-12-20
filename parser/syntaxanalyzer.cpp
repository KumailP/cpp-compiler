#include "syntaxanalyzer.h"

using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer(bool verbose)
{
    this->verbose = verbose;
}

bool SyntaxAnalyzer::saveCursor()
{
    this->savedCursor = this->cursor;
    return true;
}

bool SyntaxAnalyzer::backtrack()
{
    if (this->verbose)
        cout << "CURSOR RESET TO: " << this->savedCursor << endl;
    this->cursor = this->savedCursor;
    return true;
}

bool SyntaxAnalyzer::analyze(vector<Token> tokens)
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

Token SyntaxAnalyzer::getNextToken()
{
    Token nextToken = this->tokens[cursor];
    this->cursor++;
    return nextToken;
}

Token SyntaxAnalyzer::peekNextToken()
{
    Token nextToken = this->tokens[cursor];
    return nextToken;
}

bool SyntaxAnalyzer::term(string expected_val)
{
    // if (peekNextToken().val == ";")
    //     return true;
    if (this->verbose)
        cout << peekNextToken().val << " == " << expected_val << endl;
    return getNextToken().val == expected_val;
}

bool SyntaxAnalyzer::termType(string expected_type)
{
    if (this->verbose)
        cout << peekNextToken().val << ", " << peekNextToken().type << " == " << expected_type << endl;
    return getNextToken().type == expected_type;
}

bool SyntaxAnalyzer::start()
{
    return (termType("id") && term("main") && term("(") && termType("id") && term(")") && term("{") && statement() && term("}"));
}

bool SyntaxAnalyzer::statement()
{
    return (saveCursor() && expression_statement() && term(";") && statement()) ||
           (backtrack() && saveCursor() && conditional_statement() && term(";") && statement()) ||
           (backtrack() && saveCursor() && iteration_statement() && statement()) ||
           (backtrack());
    // return (saveCursor() && expression_statement() && statement()) ||
    //        (backtrack() && saveCursor() && conditional_statement() && statement()) ||
    //        (backtrack() && saveCursor() && iteration_statement() && statement()) ||
    //        (backtrack() && true);
    // return (saveCursor() && expression_statement()) ||
    //        (backtrack() && saveCursor() && iteration_statement());
}

bool SyntaxAnalyzer::expression_statement()
{
    return (saveCursor() && inc_dec_statement()) ||
           (backtrack() && saveCursor() && declaration_statement()) ||
           (backtrack() && saveCursor() && assignment_statement());
}

bool SyntaxAnalyzer::condition()
{
    // i<5
    return (saveCursor() && LT_OP()) ||
           (backtrack() && saveCursor() && GT_OP()) ||
           (backtrack() && saveCursor() && EQ_OP()) ||
           (backtrack() && saveCursor() && LE_OP()) ||
           (backtrack() && saveCursor() && GE_OP()) ||
           (backtrack() && saveCursor() && NE_OP());
}

bool SyntaxAnalyzer::LT_OP()
{
    return termType("id") && term("<") && termType("num");
}

bool SyntaxAnalyzer::GT_OP()
{
    return termType("id") && term(">") && termType("num");
}

bool SyntaxAnalyzer::LE_OP()
{
    return termType("id") && term("<") && term("=") && termType("num");
}

bool SyntaxAnalyzer::GE_OP()
{
    return termType("id") && term(">") && term("=") && termType("num");
}

bool SyntaxAnalyzer::EQ_OP()
{
    return termType("id") && term("=") && term("=") && termType("num");
}

bool SyntaxAnalyzer::NE_OP()
{
    return termType("id") && term("!") && term("=") && termType("num");
}

bool SyntaxAnalyzer::conditional_statement()
{
    return (saveCursor() && term("if") && term("(") && condition() && term(")") && compound_statement());
}

bool SyntaxAnalyzer::compound_statement()
{
    return (saveCursor() && term("{") && statement() && term("}")) ||
           (backtrack() && saveCursor() && statement());
}

bool SyntaxAnalyzer::iteration_statement()
{
    // while '(' expression ')' statement
    //                 | do statement while '(' expression ')' ';'
    //                 | for '(' expression_statement expression_statement ')' statement
    //                 | for '(' expression_statement expression_statement expression ')' statement
    return (saveCursor() && while_loop()) ||
           (backtrack() && saveCursor() && do_while_loop());
}

bool SyntaxAnalyzer::do_while_loop()
{
    return (term("exec") && term("{") && statement() && term("}") && term("during") && term("(") && condition() && term(")"));
}

bool SyntaxAnalyzer::while_loop()
{
    return (term("during") && term("(") && condition() && term(")") && term("{") && statement() && term("}"));
}

bool SyntaxAnalyzer::declaration_statement()
{
    return (type_specifier() && termType("id") && term("=") && termType("num"));
}

bool SyntaxAnalyzer::assignment_statement()
{
    return (termType("id") && term("=") && expression());
}

bool SyntaxAnalyzer::expression()
{
    cout << "EXPRESSION" << endl;
    return (saveCursor() && termType("id") && term("=") && termType("id")) ||
            (backtrack() && saveCursor() && termType("id") && term("*") && termType("id")) ||
            (backtrack() && saveCursor() && termType("id") && term("+") && termType("id")) ||
            (backtrack() && saveCursor() && termType("id") && term("/") && termType("id")) ||
            (backtrack() && saveCursor() && termType("id") && term("-") && termType("id")) ||
           (backtrack() && saveCursor() && termType("id")) ||
           (backtrack() && saveCursor() && termType("num")) ||
           (backtrack() && true);
}

bool SyntaxAnalyzer::inc_dec_statement()
{
    return (saveCursor() && inc_statement()) ||
           (backtrack() && saveCursor() && dec_statement());
}

bool SyntaxAnalyzer::dec_statement()
{
    // cout << "INC STATEMENT" << endl;
    return (termType("id") && term("-") && term("-"));
}

bool SyntaxAnalyzer::inc_statement()
{
    // cout << "INC STATEMENT" << endl;
    return (termType("id") && term("+") && term("+"));
}

bool SyntaxAnalyzer::type_specifier()
{
    return termType("id");
}