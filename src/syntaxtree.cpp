#include "syntaxtree.hpp"

//variables and function storage
std::vector<Variable> scriptVariables;
std::vector<constantVariable> scriptConstantVariables;
std::vector<discVariable> scriptDiscVariables;
std::vector<syntaxNode> functions;

syntaxNode::syntaxNode(){}
syntaxNode::syntaxNode(std::string type, std::string syntax, std::string data):_type(std::move(type)),_syntax(std::move(syntax)),_data(std::move(data)){}
syntaxNode parseSyntax(syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  //std::cout << "syntax: " << syntax._syntax << '\n';
  //for (auto i : arguments){std::cout << " - args: " << i._syntax << '\n';}
  if (syntax._type != "literal")
  {
    if (syntax._syntax == "print")
    {
      printMethod(scriptVariables, syntax, arguments, currentScope);
    }
    else if (syntax._syntax == "input")
    {
      return syntaxNode("literal", inputMethod(scriptVariables, arguments),syntax._syntax);
    }
    else if (syntax._syntax == "add")
    {
      //std::cout << "add : " << addNums(scriptVariables, syntax, arguments, currentScope) << '\n';
      return syntaxNode("literal", addNums(scriptVariables, syntax, arguments, currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "subtract")
    {
      return syntaxNode("literal", subtractNums(scriptVariables, syntax, arguments, currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "multiply")
    {
      return syntaxNode("literal", multiplyNums(scriptVariables, syntax, arguments, currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "divide")
    {
      return syntaxNode("literal", divideNums(scriptVariables, syntax, arguments, currentScope),syntax._syntax);
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
      return syntaxNode("literal", equal(scriptVariables,syntax,arguments,currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "greater")
    {
      return syntaxNode("literal", greater(scriptVariables,syntax,arguments,currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "less")
    {
      return syntaxNode("literal", less(scriptVariables,syntax,arguments,currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "lessOrEqual")
    {
      return syntaxNode("literal", lessOrEqual(scriptVariables,syntax,arguments,currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "greaterOrEqual")
    {
      return syntaxNode("literal", greaterOrEqual(scriptVariables,syntax,arguments,currentScope),syntax._syntax);
    }
    else if (syntax._syntax == "exec")
    {
      return syntaxNode("literal", functionInstantiateMethod(syntax, functions, arguments),syntax._syntax);
    }
    else if (syntax._syntax == "if")
    {return syntax;}
    else if (syntax._syntax == "elif")
    {return syntax;}
    else if (syntax._syntax == "el")
    {return syntax;}
    else
    {
      for(syntaxNode i : functions)
      {
        //std::cout << "Function:" << syntax._syntax << '\n';
        if (i._syntax == syntax._syntax)
        {
          //std::cout << "Function:" << i._syntax << '\n';
          itterateScope(i);
        }
      }
    }
  }
  return syntax;
}

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments)
{
  std::vector<syntaxNode> returnVec = {};
  for (std::size_t i = 0; i < arguments.size(); ++i)
  {
    if (!arguments[i]._arguments.empty())
    {
      if (arguments[i]._type != "literal")
      {
        returnVec.push_back(parseSyntax(arguments[i], itterateArguments(arguments[i]._arguments), arguments[i]._scope));
      }
      else
      {
        returnVec.push_back(arguments[i]);
      }
      /*for (syntaxNode j : argvec) {std::cout << "argvec: " << j._syntax << '\n';}
      for (syntaxNode j : arguments) {std::cout << "args: " << j._syntax << '\n';
      for (syntaxNode k : j._arguments) {std::cout << "args2: " << k._syntax << '\n';}}
      returnVec.insert(it, argvec.begin(), argvec.end());*/

    }
    else
    {
      if (arguments[i]._scope.empty())//scope empty
      {
        if (arguments[i]._type == "literal")
        {
          returnVec.push_back(arguments[i]);
        }
        else if (arguments[i]._type == "variable")
        {
          for (Variable q : scriptVariables)
          {
            if (q.getVariableName() == arguments[i]._syntax)
            {
              //std::cout << " SPECIAL varname: " << q.getVariableName() << " SPECIAL syntax: " << i->_syntax << '\n' << " SPECIAL VALUE: " << q.getVariableValue()[0] << '\n';
              returnVec.push_back(syntaxNode("literal", q.getVariableValue()[0],arguments[i]._syntax));
              break;
            }
          }

        }
        else
        {
          returnVec.push_back(parseSyntax(arguments[i], arguments[i]._arguments, arguments[i]._scope));
        }
        //std::cout << returnVec.back()._syntax <<" segf\n";
      }
      else
      {
        //scope not empty
        while(!arguments[i]._scope.empty())
        {
          itterateScopeRecursion(arguments[i]);
        }
        return returnVec;
      }
    }
  }
  return returnVec;
}
//Only execute elses if the previous syntax in the scope is an if or else if and it evaluated to false.
std::vector<std::string> conditionDepthFlag;
unsigned scopeDepth = 0;
void insertConditionFlag(std::string flag)
{
  if (conditionDepthFlag.capacity() > scopeDepth)
  {
    conditionDepthFlag[scopeDepth] = flag;
  }
  else
  {
    conditionDepthFlag.push_back(flag);
  }
}
std::string itterateScopeRecursion(syntaxNode currentScope)
{
  //SCOPES
  ++scopeDepth;
  if (currentScope._syntax == "if")//Check if syntax is a scope then recurse if statement true
  {
    insertConditionFlag("true");
    if (itterateArguments(currentScope._arguments)[0]._syntax != "1")
    {
      insertConditionFlag("fail");
      --scopeDepth;
      return currentScope._type;
    }
  }
  else if (currentScope._syntax == "elif")//Check if syntax is a scope then recurse if statement true
  {
    if (conditionDepthFlag[scopeDepth] == "triggered" || conditionDepthFlag[scopeDepth] == "true")
    {
      insertConditionFlag("triggered");
      --scopeDepth;
      return currentScope._type;
    }
    else if (itterateArguments(currentScope._arguments)[0]._syntax != "1")
    {
      insertConditionFlag("fail");
      --scopeDepth;
      return currentScope._type;
    }
    insertConditionFlag("true");
  }
  else if (currentScope._syntax == "el")//Check if syntax is a scope then recurse if statement true
  {
    //std::cout << currentScope._backNeighbor->_syntax;
    if (conditionDepthFlag[scopeDepth] == "triggered" || conditionDepthFlag[scopeDepth] != "true")
    {
      //currentScope.scopeIndex = 0;
      --scopeDepth;
      return currentScope._type;
    }
  }
  while (currentScope.scopeIndex < currentScope._scope.size())
  {
    if (currentScope._syntax == "exec")//Check if syntax is a scope then recurse if statement true
    {
      bool functionInstantiated = false;
      for(syntaxNode i : functions)
      {
        if (i._syntax == currentScope._arguments[0]._syntax)
        {
          functionInstantiated = true;
          break;
        }
      }
      if (functionInstantiated == false)
      {
        parseSyntax(currentScope, itterateArguments(currentScope._arguments), currentScope._scope);
        ++currentScope.scopeIndex;
        --scopeDepth;
        return currentScope._type;
      }
    }
    itterateScopeRecursion(currentScope._scope[currentScope.scopeIndex]);
    parseSyntax(currentScope._scope[currentScope.scopeIndex], itterateArguments(currentScope._scope[currentScope.scopeIndex]._arguments), currentScope._scope[currentScope.scopeIndex]._scope);
    ++currentScope.scopeIndex;
    //currentScope._scope.pop();
  }
  --scopeDepth;
  return currentScope._type;
}

void  itterateScope(syntaxNode currentSyntax)
{
  currentSyntax.scopeIndex = 0;
  itterateScopeRecursion(currentSyntax);
  return;
}
