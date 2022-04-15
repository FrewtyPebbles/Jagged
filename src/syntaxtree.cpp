#include "syntaxtree.hpp"

//variables and function storage
//std::vector<Variable> scriptVariables;
VarMap scriptVariables;
std::vector<constantVariable> scriptConstantVariables;
std::vector<discVariable> scriptDiscVariables;
std::vector<syntaxNode> functions;
std::vector<std::string> conditionDepthFlag;
unsigned scopeDepth = 0;

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
      setMethod(&scriptVariables[arguments[0]._syntax], scriptVariables,syntax,arguments,currentScope);// sets arg 0 variable to arg 1
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
      return syntaxNode("literal", functionInstantiateMethod(scriptVariables, syntax, functions, arguments),syntax._syntax);
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
        if (i._syntax == syntax._syntax)
        {
          itterateScope(i, syntax._arguments);
          break;
        }
      }
    }
  }
  return syntax;
}

std::vector<syntaxNode> itterateArguments(std::string type, std::vector<syntaxNode> & arguments, syntaxNode userFunction)
{
  std::vector<syntaxNode> returnVec = {};
  if(type == "function")
  {
    //std::cout << "itter args\n";
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
      //std::cout << "ARG : " << arguments[i]._syntax << '\n';
      if (!arguments[i]._arguments.empty())
      {
        if (arguments[i]._type != "literal")
        {
          scriptVariables[userFunction._arguments[i + 1]._syntax].setVariable(parseSyntax(arguments[i], itterateArguments(arguments[i]._type, arguments[i]._arguments), arguments[i]._scope)._syntax);
          //returnVec.push_back(parseSyntax(arguments[i], itterateArguments(arguments[i]._type, arguments[i]._arguments), arguments[i]._scope));
        }
        else
        {
          scriptVariables[userFunction._arguments[i + 1]._syntax].setVariable(arguments[i]._syntax);
          //returnVec.push_back(arguments[i]);
        }
      }
      else
      {
        if (arguments[i]._scope.empty())//scope empty
        {
          if (arguments[i]._type == "literal")
          {
            scriptVariables[userFunction._arguments[i + 1]._syntax].setVariable(arguments[i]._syntax);
            //returnVec.push_back(arguments[i]);
          }
          else if (arguments[i]._type == "variable")
          {
            scriptVariables[userFunction._arguments[i + 1]._syntax].setVariable(scriptVariables[arguments[i]._syntax].getVariableValue()[0]);
            //returnVec.push_back(syntaxNode("literal", scriptVariables[arguments[i]._syntax].getVariableValue()[0],arguments[i]._syntax));
          }
          else
          {
            scriptVariables[userFunction._arguments[i + 1]._syntax].setVariable(parseSyntax(arguments[i], arguments[i]._arguments, arguments[i]._scope)._syntax);
            //returnVec.push_back(parseSyntax(arguments[i], arguments[i]._arguments, arguments[i]._scope));
          }
        }
        else
        {
          //scope not empty
          while(!arguments[i]._scope.empty())
          {
            std::vector<syntaxNode> defaultVec = {};
            itterateScope(arguments[i], defaultVec);
          }
          return returnVec;
        }
      }
    }
  }
  else
  {
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
      if (!arguments[i]._arguments.empty())
      {
        if (arguments[i]._type != "literal")
        {
          returnVec.push_back(parseSyntax(arguments[i], itterateArguments(arguments[i]._type, arguments[i]._arguments), arguments[i]._scope));
        }
        else
        {
          returnVec.push_back(arguments[i]);
        }
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
            returnVec.push_back(syntaxNode("literal", scriptVariables[arguments[i]._syntax].getVariableValue()[0],arguments[i]._syntax));
          }
          else
          {
            returnVec.push_back(parseSyntax(arguments[i], arguments[i]._arguments, arguments[i]._scope));
          }
        }
        else
        {
          //scope not empty
          while(!arguments[i]._scope.empty())
          {
            std::vector<syntaxNode> defaultVec = {};
            itterateScope(arguments[i], defaultVec);
          }
          return returnVec;
        }
      }
    }
  }
  return returnVec;
}
//Only execute elses if the previous syntax in the scope is an if or else if and it evaluated to false.
void insertConditionFlag(std::string flag)
{
  if (conditionDepthFlag.capacity() == 0) conditionDepthFlag.push_back("global");
  if (conditionDepthFlag.capacity() > scopeDepth)
  {
    conditionDepthFlag[scopeDepth] = flag;
  }
  else
  {
    conditionDepthFlag.push_back(flag);
  }
  return;
}
std::string itterateScopeRecursion(syntaxNode currentScope, std::vector<syntaxNode> & userArguments)
{
  //SCOPES
  //std::cout << currentScope._syntax << " current Scope!\n";
  if (currentScope._syntax == "if")//Check if syntax is a scope then recurse if statement true
  {
    if (itterateArguments(currentScope._type, currentScope._arguments)[0]._syntax != "1")
    {
      insertConditionFlag("fail");
      return currentScope._type;
    }
    insertConditionFlag("true");
  }
  else if (currentScope._syntax == "elif")//Check if syntax is a scope then recurse if statement true
  {
    if (conditionDepthFlag[scopeDepth] != "fail")
    {
      insertConditionFlag("triggered");
      return currentScope._type;
    }
    else if (itterateArguments(currentScope._type, currentScope._arguments)[0]._syntax != "1")
    {
      insertConditionFlag("fail");
      return currentScope._type;
    }
    insertConditionFlag("true");
  }
  else if (currentScope._syntax == "el")//Check if syntax is a scope then recurse if statement true
  {
    if (conditionDepthFlag[scopeDepth] != "fail")
    {
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
        parseSyntax(currentScope, itterateArguments(currentScope._type, currentScope._arguments), currentScope._scope);
        ++currentScope.scopeIndex;
        return currentScope._type;
      }
    }
    std::vector<syntaxNode> functionArgs;
    if (currentScope._type == "function" && currentScope.scopeIndex == 0)
    {
      //std::cout << currentScope._syntax << " == type func\n";
      //std::cout << "is Function 2!!!\n";
      insertConditionFlag("function");
      functionArgs = itterateArguments(currentScope._type, userArguments, currentScope);
    }
    else
    {
      //std::cout << currentScope._syntax << " != type func\n";
      functionArgs = itterateArguments(currentScope._scope[currentScope.scopeIndex]._type, currentScope._scope[currentScope.scopeIndex]._arguments);
    }
    ++scopeDepth;
    //std::cout << " segf 1\n" << currentScope._scope[currentScope.scopeIndex]._syntax << " - syntax\n" << currentScope._scope[currentScope.scopeIndex]._arguments[0]._syntax << " - arg\n";
    itterateScopeRecursion(currentScope._scope[currentScope.scopeIndex], userArguments);
    //std::cout << " segf 2\n";

    parseSyntax(currentScope._scope[currentScope.scopeIndex], functionArgs, currentScope._scope[currentScope.scopeIndex]._scope);
    ++currentScope.scopeIndex;
    --scopeDepth;
  }

  return currentScope._type;
}

void  itterateScope(syntaxNode currentSyntax, std::vector<syntaxNode> & userArguments)
{
  currentSyntax.scopeIndex = 0;
  /*if (currentSyntax._type == "function")
  {
    //std::cout << "is Function 1!!!\n";
    itterateArguments(currentSyntax._type, userArguments, currentSyntax);
  }*/
  itterateScopeRecursion(currentSyntax, userArguments);
  return;
}
