#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <new>
#pragma once

/*pseudo

-syntax node that points to other syntax nodes in a queue attribute.
--queue attribute uses string datatype then parses the data into its correct type when executing the syntax tree.

itterate recursively through scope in node executing node.

*/

class syntaxNode
{
public:
  syntaxNode();
  syntaxNode(std::string syntax);
  std::string _syntax;  // the syntax to be parsed in the current node
  std::vector<syntaxNode>  _arguments;  // arguments for the scope ex: (arg1, arg2, arg3)
  std::queue<syntaxNode> _scope;  // the queue of syntax nodes within the scope of this syntaxNode -- if it is empy it returns to the parent syntax node.
};

std::string parseSyntax(std::string grammar, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope);  //parse the current syntax

void itterateScopeRecursion(syntaxNode currentScope);

void itterateScope(syntaxNode currentSyntax);  //itterate recursively through syntax tree

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments);  //itterate through arguments
