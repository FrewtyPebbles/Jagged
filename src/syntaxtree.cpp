#include "syntaxtree.hpp"


syntaxNode::syntaxNode(){}
syntaxNode::syntaxNode(std::string type, std::string syntax):_type(std::move(type)),_syntax(std::move(syntax)){}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  for (std::vector<syntaxNode>::iterator it = begin(arguments); it != end(arguments); ++it)
  {
    syntaxNode * i = &(*it);
    if (i->_scope.empty())//scope empty
    {
      returnVec.push_back(parseSyntax(*i, i->_arguments, i->_scope));
    }
    else
    {
      //scope not empty
      while(!i->_scope.empty())
      {
        itterateScopeRecursion(*i);
      }
      return {};
    }
  }
  return returnVec;
}

syntaxNode parseSyntax(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  if (syntax._syntax == "print")
  {
    printMethod(syntax, arguments, currentScope);
  }
  else if (syntax._syntax == "input")
  {
    inputMethod(arguments);
  }
  else if (syntax._syntax == "add")
  {
    return syntaxNode("literal", addNums(syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "subtract")
  {
    return syntaxNode("literal", subtractNums(syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "multiply")
  {
    return syntaxNode("literal", multiplyNums(syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "divide")
  {
    return syntaxNode("literal", divideNums(syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "open")
  {
    std::cout << "Opened." << '\n';

  }
  else if (syntax._syntax == "close")
  {
    std::cout << "Closed." << '\n';

  }
  else if (syntax._syntax == "jag")
  {
    std::cout << "Jagged." << '\n';

  }
  else if (syntax._syntax == "VAR")
  {
    varMethod(arguments);
  }
  return syntax;
}

std::string itterateScopeRecursion(syntaxNode currentScope)
{
  while (!currentScope._scope.empty())
  {
    itterateScopeRecursion(currentScope._scope.front());
    parseSyntax(currentScope._scope.front(), itterateArguments(currentScope._scope.front()._arguments), currentScope._scope.front()._scope);
    currentScope._scope.pop();
  }
  return currentScope._syntax;
}

void  itterateScope(syntaxNode currentSyntax)
{
  itterateScopeRecursion(currentSyntax);
  return;
}
