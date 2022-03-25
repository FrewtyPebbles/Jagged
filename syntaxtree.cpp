#include "syntaxtree.hpp"

syntaxNode::syntaxNode(){}
syntaxNode::syntaxNode(std::string syntax):_syntax(std::move(syntax)){}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  for (std::vector<syntaxNode>::iterator it = arguments.begin(); it != arguments.end(); ++it)
  {
    syntaxNode * i = &(*it);
    if (i->_scope.empty())//scope empty
    {
      returnVec.push_back(syntaxNode(parseSyntax(i->_syntax, i->_arguments, i->_scope)));
    }
    else
    {
      //scope not empty
      while(!i->_scope.empty())
      {
        std::cout << "DEBUG:: (itterateScope) Parent : " <<  i->_syntax << " - Back of scope : " << i->_scope.back()._syntax << '\n';
        itterateScopeRecursion(*i);
        //i->_scope.pop();
      }
      return {};
    }
  }
  //std::cout << "Itterated Arguments.\n";
  return returnVec;
}

std::string parseSyntax(std::string grammar, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  if (grammar == "print")
  {
    std::cout << "print" << '\n';

  }
  else if (grammar == "input")
  {
    std::string inputTest;
    std::cin >> inputTest;

  }
  else if (grammar == "open")
  {
    std::cout << "open" << '\n';

  }
  else if (grammar == "close")
  {
    std::cout << "close" << '\n';

  }
  else if (grammar == "Jag")
  {
    std::cout << "Jag" << '\n';

  }
  //std::cout << "Parsed Grammar.\n";
  return grammar;
}

void itterateScopeRecursion(syntaxNode currentScope)
{
  while (!currentScope._scope.empty())
  {
    itterateScopeRecursion(currentScope._scope.front());
    parseSyntax(currentScope._scope.front()._syntax, itterateArguments(currentScope._scope.front()._arguments), currentScope._scope.front()._scope);
    currentScope._scope.pop();
  }
  return;
}

void  itterateScope(syntaxNode currentSyntax)
{
  //arguments debug
  for (syntaxNode i : currentSyntax._arguments){std::cout << "DEBUG:: (itterateScope) Parent : " <<  currentSyntax._syntax << " - Argument : " << i._syntax << '\n';}
      itterateScopeRecursion(currentSyntax);
  return;
}
