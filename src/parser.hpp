#include "syntaxtree.hpp"
#pragma once



int scanSource(std::string& source, std::stack<syntaxNode*> & scopeStack);

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument);
