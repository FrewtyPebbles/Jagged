#include "syntaxtree.hpp"


std::vector<Variable> scriptVariables;
std::vector<constantVariable> scriptConstantVariables;
std::vector<discVariable> scriptDiscVariables;

syntaxNode::syntaxNode(){}
syntaxNode::syntaxNode(std::string syntax):_syntax(std::move(syntax)){}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  for (std::vector<syntaxNode>::iterator it = begin(arguments); it != end(arguments); ++it)
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
    for(unsigned i = 0; i < scriptVariables.size(); ++i)
    {
      if (scriptVariables[i].getVariableName() == arguments[0]._syntax)
      {
        std::cout << scriptVariables[i].getVariableValue()[0] << '\n';
        break;
      }
    }
  }
  else if (grammar == "input")
  {
    std::string input;
    for(unsigned i = 0; i < scriptVariables.size(); ++i)
    {
      if (scriptVariables[i].getVariableName() == arguments[0]._syntax)
      {
        getline(std::cin, input);
        scriptVariables[i].setVariable(input);
        break;
      }
    }

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
    Variable tempVar(arguments[0], arguments[0]._syntax, rhs);
    scriptVariables.push_back(tempVar);
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
  itterateScopeRecursion(currentSyntax);
  return;
}
