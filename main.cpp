#include "lexical_analyzer/lexer.h"
#include "parser/parser.h"

using namespace std;

int main()
{
    string inputFileName = "input.sk";
    // string outputFileName = "outputFile.txt";
    Lexer lexer(inputFileName);

    vector<Token> tokens;
    tokens = lexer.generateTokens();

    // cout << "TOKENS: " << endl;
    // lexer.printTokens();

    Parser parser;
    parser.parse(tokens);

    // string outputFileName;
    // cout << "Enter output file name: ";
    // cin >> outputFileName;
    // outputFileName = "output.txt";
    // lexer.printTokensInFile(outputFileName);
    return 0;
}