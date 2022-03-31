#include "syntaxtree.hpp"

//variables and function storage
std::vector<Variable> scriptVariables;
std::vector<constantVariable> scriptConstantVariables;
std::vector<discVariable> scriptDiscVariables;
std::vector<syntaxNode> functions;

std::string parseArguments(unsigned argumentnum, syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{
  std::string argstr;
  if (arguments[argumentnum]._type == "variable")
  {
    for(unsigned i = 0; i < scriptVariables.size(); ++i)
    {
      if (scriptVariables[i].getVariableName() == arguments[argumentnum]._syntax)
      {
        argstr = scriptVariables[i].getVariableValue()[0];
        break;
      }
    }
  }
  else if (arguments[argumentnum]._type == "literal")
  {
    argstr = arguments[argumentnum]._syntax;
  }
  return argstr;
}
//Use reverse pemdas. s a d m e p

std::string subtractNums(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(0, syntax, arguments, currentScope).c_str(), nullptr) - strtof(parseArguments(1, syntax, arguments, currentScope).c_str(), nullptr));}//BUG

std::string addNums(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(0, syntax, arguments, currentScope).c_str(), nullptr) + strtof(parseArguments(1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string divideNums(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(0, syntax, arguments, currentScope).c_str(), nullptr) / strtof(parseArguments(1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string multiplyNums(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(0, syntax, arguments, currentScope).c_str(), nullptr) * strtof(parseArguments(1, syntax, arguments, currentScope).c_str(), nullptr));}

void printMethod(syntaxNode syntax, std::vector<syntaxNode> arguments, std::queue<syntaxNode> & currentScope)
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

void inputMethod( std::vector<syntaxNode> arguments )
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
void varMethod(std::vector<syntaxNode> arguments)
{
  std::vector<std::string> rhs;
  rhs.push_back(arguments[1]._syntax);
  Variable tempVar(arguments[0], arguments[0]._syntax, rhs);
  scriptVariables.push_back(tempVar);
}
