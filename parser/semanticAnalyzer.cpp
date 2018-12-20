#include "semanticanalyzer.h"

using namespace std;

SemanticAnalyzer::SemanticAnalyzer()
{
    return;
}

bool SemanticAnalyzer::analyze(vector<Token> tokens)
{
    this->tokens = tokens;

    map<string, string>::iterator it_found;

    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        // cout << tokens[i].val << " | " << tokens[i].type << endl;
        if (tokens[i].type == "id")
        {
            if (tokens[i + 1].type == "id" && (tokens[i].val == "void" || tokens[i].val == "int" || tokens[i].val == "float" || tokens[i].val == "bool" || tokens[i].val == "string"))
            {
                string findToken = tokens[i + 1].val;
                cout << "FINDING: '" << findToken << "'" << endl;
                it_found = declaredItems.find(findToken);
                // it_found = declaredItems.find(tokens[i + 1].val);

                if (it_found != declaredItems.end())
                {
                    cout << "ERROR: RE-DECLARATION OF " << it_found->first << "." << endl;
                    return 1;
                }
                else
                {
                    declaredItems.insert(pair<string, string>(tokens[i + 1].val, tokens[i].val));
                }
                it_found = declaredItems.begin();
            }
        }

        if (tokens[i+2].type == "num" && tokens[i+2].type == "str" && tokens[i + 1].type == "symb")
        {
            if (tokens[i].type != tokens[i + 2].type){
                cout << "ERROR: Type mismatch. Trying to set value of " << tokens[i].type << " to " << tokens[i+2].type << "." << endl;
                return 1;
            }
        }
    }

    cout << "MAP:" << endl;

    std::map<string, string>::iterator it = declaredItems.begin();
    for (it = declaredItems.begin(); it != declaredItems.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}