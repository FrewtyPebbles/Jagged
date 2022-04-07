#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <new>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <string.h>
#include <iomanip>
#include <algorithm> //find()
#include <memory>
#pragma once

/*pseudo

-syntax node that points to other syntax nodes in a queue attribute.
--queue attribute uses string datatype then parses the data into its correct type when executing the syntax tree.

itterate recursively through scope in node executing node.

*/

class syntaxNode
{
public:
  syntaxNode();
  syntaxNode(std::string type, std::string syntax);
  std::string _type;
  std::string _syntax;  // the syntax to be parsed in the current node
  std::vector<syntaxNode>  _arguments;  // arguments for the scope ex: (arg1, arg2, arg3)
  std::vector<syntaxNode> _scope;  // the queue of syntax nodes within the scope of this syntaxNode -- if it is empy it returns to the parent syntax node.
  std::size_t scopeIndex = 0;
  std::string _data;
  syntaxNode* _parent;
  syntaxNode* _backNeighbor;
};

syntaxNode parseSyntax(syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);  //parse the current syntax

std::string itterateScopeRecursion(syntaxNode currentScope);

void itterateScope(syntaxNode currentSyntax);  //itterate recursively through syntax tree

std::vector<syntaxNode> itterateArguments(std::vector<syntaxNode> & arguments);  //itterate through arguments


class Variable
{
private:
  std::string varName;
  std::vector<std::string> data;
public:
  Variable();
  Variable(syntaxNode _instantiatedScope, std::string _varName, std::vector<std::string> _data);
  void setVariable(std::string _varValue);
  void appendVariable(std::string _varValue);
  std::string& getVariableName();
  std::vector<std::string>& getVariableValue();
  syntaxNode instantiatedScope;
};

class constantVariable
{
private:
  std::string varName;
  std::vector<std::string> data;
public:
  constantVariable();
  constantVariable(syntaxNode _instantiatedScope, std::string _varName, std::vector<std::string> _data);
  std::string& getVariableName();
  std::vector<std::string>& getVariableValue();
  syntaxNode instantiatedScope;
};

class discVariable
{
private:
  std::string varName;
  std::string filePath;
  std::vector<std::string> data;
public:
  discVariable();
  discVariable(syntaxNode _instantiatedScope, std::string _varName, std::vector<std::string> _data, std::string _filePath);
  std::string readName();
  std::vector<std::string> readData();
  void deleteVariable();
  syntaxNode instantiatedScope;
};
void parseVariable(std::string Type, std::string name, std::string value); //feeds variable into data from parser.cpp

//methods

std::string parseArguments(std::vector<Variable>& scriptVariables1, unsigned argumentnum, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);

//math functions
std::string subtractNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string addNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string divideNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string multiplyNums(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);

//Comparison functions
std::string equal(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string less(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string greater(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string greaterOrEqual(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string lessOrEqual(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
//User Functions
std::string functionInstantiateMethod(syntaxNode Instantiation, std::vector<syntaxNode>& functions, std::vector<syntaxNode> arguments);
//Standard library functions
void printMethod(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
std::string inputMethod(std::vector<Variable>& scriptVariables, std::vector<syntaxNode> arguments );

//VARIABLE METHODS
void varMethod(std::vector<Variable>& scriptVariables, std::vector<syntaxNode> arguments);
void setMethod(std::vector<Variable>& scriptVariables, syntaxNode syntax, std::vector<syntaxNode> arguments, std::vector<syntaxNode> & currentScope);
