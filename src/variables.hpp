#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
//#include once "syntaxtree.hpp"
#pragma once


class Variable
{
private:
  std::string varName;
  std::vector<std::string> data[1];
public:
  Variable();
  Variable(syntaxNode * _instantiatedScope, std::string _varName, std::vector<std::string> _data);
  void setVariable(std::string _varName);
  std::string& getVariableName();
  std::string& getVariableValue();
  syntaxNode * instantiatedScope;
};

class constantVariable
{
private:
  std::string varName;
  std::vector<std::string> data[1];
public:
  constantVariable();
  constantVariable(syntaxNode * _instantiatedScope, std::string _varName, std::vector<std::string> _data);
  std::string& getVariableName();
  std::string& getVariableValue();
  syntaxNode * instantiatedScope;
};

class discVariable
{
private:
  std::string varName;
  std::string filePath;
  std::vector<std::string> data[1];
public:
  discVariable();
  discVariable(syntaxNode * _instantiatedScope, std::string _varName, std::vector<std::string> _data, std::string _filePath);
  std::string readName();
  std::vector<std::string> readData();
  void deleteVariable();
  syntaxNode instantiatedScope;
};

void parseVariable(std::string Type, std::string name, std::string value); //feeds variable into data from parser.cpp
