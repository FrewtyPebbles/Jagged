#include "parser.hpp"

std::vector<std::string> scopeLookupTable =
{
  "exec",
  "if",
  "ef",
  "el"
};
std::vector<std::string> grammarLookupTable =
{
  "print",
  "input",
  "open",
  "close",
  "jag",
  "VAR",
  "FIX",
  "DISC"
};
bool grammarExists = false;

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument)
{
  if (grammar != "")  //grammar pushed to arguments
  {
    syntaxNode nextSyntax;
    nextSyntax._syntax = grammar;
    grammarExists = false;
    if (isArgument)
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar) {grammarExists = true;scopeStack.top()->_arguments.push_back(nextSyntax);break;}
      }
      for (std::string _grammar : grammarLookupTable)
      {
        if (_grammar == grammar) {grammarExists = true;scopeStack.top()->_arguments.push_back(nextSyntax);break;}
      }
      //If grammar does not exist

    }
    else  //grammar pushed to scope
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar) {grammarExists = true;scopeStack.top()->_scope.push(nextSyntax); break;}
      }
      for (std::string _grammar : grammarLookupTable)
      {
        if (_grammar == grammar) {grammarExists = true;scopeStack.top()->_scope.push(nextSyntax);break;}
      }
      //if grammar does not exist

    }
    if (!grammarExists)
    {
      grammarLookupTable.push_back(grammar);
      //for (std::string _grammar : grammarLookupTable)std::cout << _grammar << '\n';
      scopeStack.top()->_arguments.push_back(nextSyntax);
    }
    scopeStack.push(&scopeStack.top()->_scope.back());  //set scope to the new scope.
  }
}

int scanSource(std::string& source)
{
  std::string keyword;
  bool isArgument = false;
  bool isQuoting = false;
  std::stack<syntaxNode*> scopeStack = {};
  scopeStack.push(new syntaxNode("global"));

  for(char character : source)
  {
    if (character == '"')
    {
      //check quoting.
      if (isQuoting == true)
      {
        //push quote
        parseGrammar(scopeStack, keyword, isArgument);
        //scopeStack.pop();
        keyword = "";
      }
      isQuoting = !isQuoting;
    }
    if (!isQuoting)
    {
      switch (character)
      {
        case ' ':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '\n':
          break;
        case '\t':
          break;
        case '\r':
          break;
        case '.':
          parseGrammar(scopeStack, keyword, isArgument);
          scopeStack.pop();
          keyword = "";
          break;
        case '=':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '+':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '-':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '*':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '/':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '&':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '|':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '{':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '}':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '(':
          parseGrammar(scopeStack, keyword, isArgument);
          isArgument = true;
          keyword = "";
          break;
        case ')':
          parseGrammar(scopeStack, keyword, isArgument);
          isArgument = false;
          scopeStack.pop();
          keyword = "";
          break;
        case '[':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case ']':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '\'':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '"':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case ',':
          parseGrammar(scopeStack, keyword, isArgument);
          //std::cout << scopeStack.top()->_syntax << '\n';
          scopeStack.pop();
          keyword = "";
          break;
        case '?':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '@':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '<':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '>':
          parseGrammar(scopeStack, keyword, isArgument);
          scopeStack.pop();
          keyword = "";
          break;
        case '!':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case ';':
          parseGrammar(scopeStack, keyword, isArgument);
          scopeStack.pop();
          keyword = "";
          break;
        case '%':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '$':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '^':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '#':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '~':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '`':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '_':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        default:
          keyword += character;
      }
    }
    else if (character != '"')
    {
      keyword += character;
    }
  }
  //std::cout << "Compiled Successfully.\n";
  //syntax tree hardcode test
  /*scopeStack.top()._scope.push(syntaxNode("print"));
  scopeStack.top()._scope.front()._scope.push(syntaxNode("close"));
  scopeStack.top()._scope.front()._scope.front()._scope.push(syntaxNode("open"));
  scopeStack.top()._scope.front()._scope.front()._scope.front()._scope.push(syntaxNode("input"));
  scopeStack.top()._scope.front()._scope.front()._scope.push(syntaxNode("Jag"));
  scopeStack.top()._scope.front()._scope.push(syntaxNode("input"));
  syntaxNode newone("input");
  newone._scope.push(syntaxNode("Jag"));
  scopeStack.top()._scope.front()._scope.push(newone);
  scopeStack.top()._scope.push(syntaxNode("close"));*/
  //scopeStack.top()._scope.front()._scope.front()._scope.push(syntaxNode("Jag"));
  itterateScope(*scopeStack.top());
  return 0;
}
