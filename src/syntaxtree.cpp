#include "syntaxtree.hpp"

//variables and function storage
std::vector<Variable> scriptVariables;
std::vector<constantVariable> scriptConstantVariables;
std::vector<discVariable> scriptDiscVariables;
std::vector<syntaxNode> functions;

syntaxNode::syntaxNode(){}
syntaxNode::syntaxNode(std::string type, std::string syntax):_type(std::move(type)),_syntax(std::move(syntax)){}

syntaxNode parseSyntax(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  if (syntax._syntax == "print")
  {
    printMethod(scriptVariables, syntax, arguments, currentScope);
  }
  else if (syntax._syntax == "input")
  {
    inputMethod(scriptVariables, arguments);
  }
  else if (syntax._syntax == "add")
  {
    //std::cout << "add : " << addNums(syntax, arguments, currentScope) << '\n';
    return syntaxNode("literal", addNums(scriptVariables, syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "subtract")
  {
    return syntaxNode("literal", subtractNums(scriptVariables, syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "multiply")
  {
    return syntaxNode("literal", multiplyNums(scriptVariables, syntax, arguments, currentScope));
  }
  else if (syntax._syntax == "divide")
  {
    return syntaxNode("literal", divideNums(scriptVariables, syntax, arguments, currentScope));
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
    varMethod(scriptVariables, arguments);
  }
  return syntax;
}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  for (std::vector<syntaxNode>::iterator it = begin(arguments); it != end(arguments); ++it)
  {
    syntaxNode * i = &(*it);
    if (!i->_arguments.empty())
    {
      returnVec.push_back(parseSyntax(*i, itterateArguments(i->_arguments), i->_scope));
      /*for (syntaxNode j : argvec) {std::cout << "argvec: " << j._syntax << '\n';}
      for (syntaxNode j : arguments) {std::cout << "args: " << j._syntax << '\n';
      for (syntaxNode k : j._arguments) {std::cout << "args2: " << k._syntax << '\n';}}
      returnVec.insert(it, argvec.begin(), argvec.end());*/

    }
    else
    {
      if (i->_scope.empty())//scope empty
      {
        if (i->_type == "literal")
        {
          returnVec.push_back(*i);
        }
        else if (i->_type == "variable")
        {
          for (Variable q : scriptVariables)
          {
            if (q.getVariableName() == i->_syntax)
            {
              //std::cout << " SPECIAL varname: " << q.getVariableName() << " SPECIAL syntax: " << i->_syntax << '\n' << " SPECIAL VALUE: " << q.getVariableValue()[0] << '\n';
              returnVec.push_back(syntaxNode("literal", q.getVariableValue()[0]));
              break;
            }
          }

        }
        else
        {
          returnVec.push_back(parseSyntax(*i, i->_arguments, i->_scope));
        }
        //std::cout << returnVec.back()._syntax <<" segf\n";
      }
      else
      {
        //scope not empty
        while(!i->_scope.empty())
        {
          itterateScopeRecursion(*i);
        }
        return returnVec;
      }
    }
  }
  return returnVec;
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
