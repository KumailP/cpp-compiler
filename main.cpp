#include "lexical_analyzer/lexer.h"

using namespace std;

int main()
{
    string inputFileName = "text.txt";
    // string outputFileName = "outputFile.txt";
    Lexer lexer(inputFileName);

    vector<Token> tokens;
    tokens = lexer.generateTokens();

    // cout << "TOKENS: " << endl;
    // lexer.printTokens();

    string outputFileName;
    // cout << "Enter output file name: ";
    // cin >> outputFileName;
    outputFileName = "output.txt";
    lexer.printTokensInFile(outputFileName);
    return 0;
}