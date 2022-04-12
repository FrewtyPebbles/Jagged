#include "syntaxtree.hpp"

std::string parseArguments(VarMap & scriptVariables, unsigned argumentnum, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  std::string argstr;
  //std::cout << "segf1.1\n";
  if (arguments[argumentnum]._type == "variable")
  {
    /*for(unsigned i = 0; i < scriptVariables.size(); ++i)
    {
      if (scriptVariables[i].getVariableName() == arguments[argumentnum]._syntax)
      {

      }
    }*/
    //std::cout << "segf1.1.1\n";
    argstr = scriptVariables[arguments[argumentnum]._syntax].getVariableValue()[0];
    //std::cout << "segf1.1.2\n";
  }
  else if (arguments[argumentnum]._type == "literal")
  {
    //std::cout << "segf1.1.3\n";
    argstr = arguments[argumentnum]._syntax;
    //std::cout << "segf1.1.4\n";
  }
  //std::cout << "segf1.2\n";
  //std::cout << syntax._syntax << '\n';
  //for (syntaxNode i : arguments){std::cout << "ARGS: " << i._syntax << '\n';}
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
{//std::cout << " arg 0 : " << parseArguments(scriptVariables, 0, syntax, arguments, currentScope) << " arg 1 : " << parseArguments(scriptVariables, 1, syntax, arguments, currentScope) << "\n";
  return std::to_string(parseArguments(scriptVariables, 0, syntax, arguments, currentScope) == parseArguments(scriptVariables, 1, syntax, arguments, currentScope));}
std::string less(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) < strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}
std::string greater(VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{//std::cout << " arg 0 : " << parseArguments(scriptVariables, 0, syntax, arguments, currentScope) << " arg 1 : " << parseArguments(scriptVariables, 1, syntax, arguments, currentScope) << "\n";
  return std::to_string(strtof(parseArguments(scriptVariables, 0, syntax, arguments, currentScope).c_str(), nullptr) > strtof(parseArguments(scriptVariables, 1, syntax, arguments, currentScope).c_str(), nullptr));}
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
      /*for(unsigned i = 0; i < scriptVariables.size(); ++i)
      {
        if (scriptVariables[i].getVariableName() == arguments[j]._syntax)
        {
          std::cout << scriptVariables[i].getVariableValue()[0];
          break;
        }
      }*/
      std::cout << scriptVariables[arguments[j]._syntax].getVariableValue()[0];
    }
    else if (arguments[j]._type == "literal")
    {
      std::cout << arguments[j]._syntax;
    }
  }
}

std::string inputMethod(VarMap& scriptVariables,  std::vector<syntaxNode> arguments )
{
  std::string input;
  //std::cout << arguments.size();
  if (arguments.size() <= 0)
  {
    getline(std::cin, input);
    //std::cout << input;
    return input;
  }
  else
  {
    getline(std::cin, input);
    scriptVariables[arguments[0]._syntax].setVariable(input);
    return input;
  }
  /*for(unsigned i = 0; i < scriptVariables.size(); ++i)
  {
    //std::cout << "varname*: " << scriptVariables[i].getVariableName() << " argument*: " << arguments[0]._syntax << '\n';
    if (scriptVariables[i].getVariableName() == arguments[0]._syntax)
    {
      //std::cout << "input:";
      getline(std::cin, input);
      scriptVariables[i].setVariable(input);
      return input;
    }
  }*/

}
//FUNCTION METHODS
std::string functionInstantiateMethod(syntaxNode Instantiation, std::vector<syntaxNode>& functions, std::vector<syntaxNode> arguments)
{
  //return if function already instantiated so multiples arent created
  for(syntaxNode i : functions)
  {
    if (i._syntax == arguments[0]._syntax) return "RETURN_VALUE";
  }
  syntaxNode newFunction;
  newFunction._type = "scope";
  newFunction._syntax = arguments[0]._syntax;
  newFunction._arguments = Instantiation._arguments;
  newFunction._scope = Instantiation._scope;
  functions.push_back(newFunction);
  return arguments[0]._syntax;
}
//VARIABLE METHODS
void varMethod(VarMap& scriptVariables, std::vector<syntaxNode> arguments)
{
  std::vector<std::string> rhs;
  rhs.push_back(arguments[1]._syntax);
  //std::cout << "VARMETHOD ARG 2 : " << arguments[0]._syntax << '\n';
  Variable tempVar(arguments[0], arguments[0]._syntax, rhs);
  scriptVariables[arguments[0]._syntax] = tempVar;
}

void setMethod(Variable * variableToSet, VarMap& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope)
{
  /*for (VarMap::iterator it = begin(scriptVariables); it != end(scriptVariables); ++it)
  {
    Variable * i(&(*it));
    if (i->getVariableName() == arguments[0]._syntax)
    {
      //std::cout << "VARNAME: " << i->getVariableName() << " ARGNAME: " << arguments[0]._syntax << '\n';
      i->setVariable(parseArguments(scriptVariables, 2, syntax, arguments, currentScope));
      break;
    }
  }*/
  //std::cout << "segf1\n";
  //std::cout << variableToSet->getVariableName() << " : VAR\n";
  variableToSet->setVariable(parseArguments(scriptVariables, 1, syntax, arguments, currentScope));
  //std::cout << "segf2\n";
}
