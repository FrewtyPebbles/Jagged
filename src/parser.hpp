#include "syntaxtree.hpp"
#pragma once

const std::string scopeLookupTable[4] =
{
  "exec",
  "if",
  "ef",
  "el"
};
const std::string grammarLookupTable[5] =
{
  "print",
  "input",
  "open",
  "close",
  "Jag"
};

int scanSource(std::string& source);

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument);
