#include "syntaxtree.hpp"


//Variables-----------------
Variable::Variable(){}
Variable::Variable(syntaxNode _instantiatedScope, std::string _varName, std::vector<std::string> _data):
instantiatedScope(_instantiatedScope),
varName(_varName),
data(_data)
{}

void Variable::setVariable(std::string _varValue,std::size_t index){data[index] = _varValue;}

std::string& Variable::getVariableName()
{
  return varName;
}

std::vector<std::string>& Variable::getVariableValue()
{
  return data;
}

//ConstantVariables---------------
constantVariable::constantVariable(){}

constantVariable::constantVariable(syntaxNode _instantiatedScope, std::string _varName, std::vector<std::string> _data):
instantiatedScope(_instantiatedScope),
varName(_varName),
data(_data)
{}

std::string& constantVariable::getVariableName()
{
  return varName;
}

std::vector<std::string>& constantVariable::getVariableValue()
{
  return data;
}

//DiscVariables
discVariable::discVariable(){}

discVariable::discVariable(syntaxNode _instantiatedScope, std::string _varName, std::vector<std::string> _data, std::string _filePath)
{
  //open file and check for variable
  //if variable exists do not change in declaration
  //else append variable to end of file with data.
}

std::string discVariable::readName()
{
  //open path and find variable.
  //return name of variable
}

std::vector<std::string> discVariable::readData()
{
  //open path and find variable.
  //return data of variable
}

void discVariable::deleteVariable()
{
  //delete variable from file.
}

//VARIABLE PARSER---------------------
void parseVariable(std::string type, std::string name, std::string value)
{

}
