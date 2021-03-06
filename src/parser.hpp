#include "syntaxtree.hpp"
#include <filesystem>
#pragma once


std::string evaluateToken(std::string source);
int scanSource(std::string source, std::stack<syntaxNode*> & scopeStack);
std::string getFileContent(std::string currentFile, std::string fileContent);
void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument);
