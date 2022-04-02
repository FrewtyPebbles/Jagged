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
  //std::cout << "type: " << syntax._type << "syntax: " << syntax._syntax << '\n';
  if (syntax._type != "literal")
  {
    if (syntax._syntax == "print")
    {
      printMethod(scriptVariables, syntax, arguments, currentScope);
    }
    else if (syntax._syntax == "input")
    {
      return syntaxNode("literal", inputMethod(scriptVariables, arguments));
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
    else if (syntax._syntax == "set")
    {
      setMethod(scriptVariables,syntax,arguments,currentScope);// sets arg 0 variable to arg 1
    }
    else if (syntax._syntax == "equal")
    {
      return syntaxNode("literal", equal(scriptVariables,syntax,arguments,currentScope));
    }
    else if (syntax._syntax == "greater")
    {
      return syntaxNode("literal", greater(scriptVariables,syntax,arguments,currentScope));
    }
    else if (syntax._syntax == "less")
    {
      return syntaxNode("literal", less(scriptVariables,syntax,arguments,currentScope));
    }
    else if (syntax._syntax == "lessOrEqual")
    {
      return syntaxNode("literal", lessOrEqual(scriptVariables,syntax,arguments,currentScope));
    }
    else if (syntax._syntax == "greaterOrEqual")
    {
      return syntaxNode("literal", greaterOrEqual(scriptVariables,syntax,arguments,currentScope));
    }
  }
  return syntax;
}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  for (std::vector<syntaxNode>::iterator it = begin(arguments); it != end(arguments); ++it)
  {
    syntaxNode * i = (&(*it));
    if (!i->_arguments.empty())
    {
      if (i->_type != "literal")
      {
        returnVec.push_back(parseSyntax(*i, itterateArguments(i->_arguments), i->_scope));
      }
      else
      {
        returnVec.push_back(*i);
      }
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
  if (currentScope._syntax == "if")//Check if syntax is a scope then recurse if statement true
  {
    if (itterateArguments(currentScope._arguments)[0]._syntax != "1")
    {
      return currentScope._type;
    }
  }
  while (!currentScope._scope.empty())
  {
    std::string lastScopeType = itterateScopeRecursion(currentScope._scope.front());
    parseSyntax(currentScope._scope.front(), itterateArguments(currentScope._scope.front()._arguments), currentScope._scope.front()._scope);
    currentScope._scope.pop();
  }
  return currentScope._type;
}

void  itterateScope(syntaxNode currentSyntax)
{
  itterateScopeRecursion(currentSyntax);
  return;
}
