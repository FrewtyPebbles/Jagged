#include "syntaxtree.hpp"

std::string parseArguments(VarMap & scriptVariables, unsigned argumentnum, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  std::string argstr;
  if (arguments[argumentnum]._type == "variable")
  {
    argstr = scriptVariables[arguments[argumentnum]._syntax].getVariableValue()[0];
  }
  else if (arguments[argumentnum]._type == "literal")
  {
    argstr = arguments[argumentnum]._syntax;
  }
  return argstr;
}

//MATH
//Use reverse pemdas. s a d m e p

std::string subtractNums(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) - strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string addNums(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) + strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string divideNums(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) / strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

std::string multiplyNums(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) * strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

//COMPARISON  return 1 or 0

std::string equal(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(parseArguments(scriptVariables, 0, syntax, arguments, currentScope) == parseArguments(scriptVariables, 1, syntax, arguments, currentScope));}
std::string less(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) < strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}
std::string greater(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) > strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}
std::string greaterOrEqual(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) >= strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}
std::string lessOrEqual(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) <= strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}

//MISC FUNCTIONS

void printMethod(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  for(unsigned j = 0; j < arguments.size(); ++j)
  {
    if (arguments[j]._type == "variable")
    {
      std::cout << scriptVariables[arguments[j]._syntax].getVariableValue()[0];
    }
    else if (arguments[j]._type == "literal")
    {
      std::cout << arguments[j]._syntax;
    }
  }
}
std::string concatenateMethod(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  std::string returnString = "";
  for(unsigned j = 0; j < arguments.size(); ++j)
  {
    if (arguments[j]._type == "variable")
    {
      returnString += scriptVariables[arguments[j]._syntax].getVariableValue()[0];
    }
    else if (arguments[j]._type == "literal")
    {
      returnString += arguments[j]._syntax;
    }
  }
  return returnString;
}

std::string inputMethod(VarMap& scriptVariables,  std::vector<syntaxNode> arguments )
{
  std::string input;
  if (arguments.size() <= 0)
  {
    getline(std::cin, input);
    return input;
  }
  else
  {
    getline(std::cin, input);
    scriptVariables[arguments[0]._syntax].setVariable(input);
    return input;
  }
}
//FUNCTION METHODS
std::string functionInstantiateMethod(VarMap& scriptVariables, syntaxNode Instantiation, std::vector<syntaxNode>& functions, std::vector<syntaxNode> arguments)
{
  //return if function already instantiated so multiples arent created
  for(syntaxNode i : functions)
  {
    if (i._syntax == arguments[0]._syntax) return "RETURN_VALUE";
  }
  syntaxNode newFunction;
  newFunction._type = "function";
  newFunction._syntax = arguments[0]._syntax;
  newFunction._arguments = Instantiation._arguments;
  std::vector<syntaxNode> varArguments;
  if (arguments.size() > 0)
  {
    for (std::size_t i = 1; i < arguments.size(); ++i)
    {
      std::vector<syntaxNode> varArguments = {syntaxNode("literal", arguments[i]._syntax, arguments[i]._syntax), syntaxNode("literal", "", "")};
      varMethod(scriptVariables, varArguments);
    }
  }
  newFunction._scope.push_back(syntaxNode("functionCall","__--NDF--__", "__--NDF--__"));//NULL DUMMY FUNCTION TO FIX DOUBLE ITTERATE ISSUE WHEN FUNCTION STARTS WITH IF.
  newFunction._scope.insert(newFunction._scope.end(), Instantiation._scope.begin(), Instantiation._scope.end());
  //newFunction._scope = Instantiation._scope;
  functions.push_back(newFunction);
  return arguments[0]._syntax;
}
//VARIABLE METHODS
void varMethod(VarMap& scriptVariables, std::vector<syntaxNode> arguments)
{
  std::vector<std::string> rhs;
  rhs.push_back(arguments[1]._syntax);
  Variable tempVar(arguments[0], arguments[0]._syntax, rhs);
  scriptVariables[arguments[0]._syntax] = tempVar;
}

void setMethod(Variable * variableToSet, VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  variableToSet->setVariable(parseArguments(scriptVariables, 1, syntax, arguments, currentScope));
}
