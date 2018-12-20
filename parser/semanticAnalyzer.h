#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H

#include <vector>
#include <map>
#include <string>
#include "../lexical_analyzer/token.h"

using namespace std;

class SemanticAnalyzer
{
public:
  vector<Token> tokens; // list of tokens
  map<string, string> declaredItems;

  SemanticAnalyzer();
  bool analyze(vector<Token> tokens);
};

#endif