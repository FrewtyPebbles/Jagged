#include "syntaxtree.hpp"


std::vector<Variable> scriptVariables;
std::vector<constantVariable> scriptConstantVariables;
std::vector<discVariable> scriptDiscVariables;

syntaxNode::syntaxNode(){}
syntaxNode::syntaxNode(std::string syntax):_syntax(std::move(syntax)){}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  //std::cout << "segfault-------0000\n";
  for (std::vector<syntaxNode>::iterator it = begin(arguments); it != end(arguments); ++it)
  {
    //std::cout << "segfault-------1111\n";
    syntaxNode * i = &(*it);
    //std::cout << "segfault-------2222\n";
    if (i->_scope.empty())//scope empty
    {
      returnVec.push_back(syntaxNode(parseSyntax(i->_syntax, i->_arguments, i->_scope)));
    }
    else
    {
      //scope not empty
      while(!i->_scope.empty())
      {
        //std::cout << "DEBUG:: (itterateScope) Parent : " <<  i->_syntax << " - Back of scope : " << i->_scope.back()._syntax << '\n';
        itterateScopeRecursion(*i);
      }
      return {};
    }
  }
  return returnVec;
}

std::string parseSyntax(std::string grammar, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  if (grammar == "print")
  {
    std::cout << scriptVariables[0].getVariableValue()[0] << '\n';
  }
  else if (grammar == "input")
  {
    std::string inputTest;
    std::cin >> inputTest;

  }
  else if (grammar == "open")
  {
    std::cout << "Opened." << '\n';

  }
  else if (grammar == "close")
  {
    std::cout << "Closed." << '\n';

  }
  else if (grammar == "jag")
  {
    std::cout << "Jagged." << '\n';

  }
  else if (grammar == "VAR")
  {
    std::vector<std::string> rhs;
    rhs.push_back(arguments[1]._syntax);
    //std::cout << "^^^rhs\n";
    Variable tempVar(arguments[0], arguments[1]._syntax, rhs);
    //std::cout << "^^^var\n";
    scriptVariables.push_back(tempVar);
    //std::cout << "^^^goodaloc\n";
  }
  return grammar;
}

std::string itterateScopeRecursion(syntaxNode currentScope)
{
  while (!currentScope._scope.empty())
  {
    itterateScopeRecursion(currentScope._scope.front());
    parseSyntax(currentScope._scope.front()._syntax, itterateArguments(currentScope._scope.front()._arguments), currentScope._scope.front()._scope);
    currentScope._scope.pop();
  }
  return currentScope._syntax;
}

void  itterateScope(syntaxNode currentSyntax)
{
  //arguments debug
  //for (syntaxNode i : currentSyntax._arguments){std::cout << "DEBUG:: (itterateScope) Parent : " <<  currentSyntax._syntax << " - Argument : " << i._syntax << '\n';}
      itterateScopeRecursion(currentSyntax);
  return;
}
