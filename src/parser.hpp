#include "syntaxtree.hpp"
#pragma once



int scanSource(std::string& source);

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument);
