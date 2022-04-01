#include "syntaxtree.hpp"



std::string parseArguments(std::vector<Variable>& scriptVariables1, unsigned argumentnum, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  std::string argstr;
  if (arguments[argumentnum]._type == "variable")
  {
    for(unsigned i = 0; i < scriptVariables1.size(); ++i)
    {
      if (scriptVariables1[i].getVariableName() == arguments[argumentnum]._syntax)
      {
        argstr = scriptVariables1[i].getVariableValue()[0];
        break;
      }
    }
  }
  else if (arguments[argumentnum]._type == "literal")
  {
    argstr = arguments[argumentnum]._syntax;
  }
  //std::cout << syntax._syntax << '\n';
  //for (syntaxNode i : arguments){std::cout << "ARGS: " << i._syntax << '\n';}
  return argstr;
}
//Use reverse pemdas. s a d m e p

std::string subtractNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) - strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}//BUG

std::string addNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) + strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string divideNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) / strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string multiplyNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) * strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

void printMethod(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  for(unsigned j = 0; j < arguments.size(); ++j)
  {
    if (arguments[j]._type == "variable")
    {
      for(unsigned i = 0; i < scriptVariables.size(); ++i)
      {
        if (scriptVariables[i].getVariableName() == arguments[j]._syntax)
        {
          std::cout << scriptVariables[i].getVariableValue()[0];
          break;
        }
      }
    }
    else if (arguments[j]._type == "literal")
    {
      std::cout << arguments[j]._syntax;
    }
  }
}

void inputMethod(std::vector<Variable>& scriptVariables,  std::vector<syntaxNode> arguments )
{
  std::string input;
  for(unsigned i = 0; i < scriptVariables.size(); ++i)
  {
    //std::cout << "varname*: " << scriptVariables[i].getVariableName() << " argument*: " << arguments[0]._syntax << '\n';
    if (scriptVariables[i].getVariableName() == arguments[0]._syntax)
    {
      //std::cout << "input:";
      getline(std::cin, input);
      scriptVariables[i].setVariable(input);
      break;
    }
  }
}
void varMethod(std::vector<Variable>& scriptVariables, std::vector<syntaxNode> arguments)
{
  std::vector<std::string> rhs;
  rhs.push_back(arguments[1]._syntax);
  //std::cout << "VARMETHOD ARG 2 : " << arguments[0]._syntax << '\n';
  Variable tempVar(arguments[0], arguments[0]._syntax, rhs);
  scriptVariables.push_back(tempVar);
}
