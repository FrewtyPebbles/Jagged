#include "parser.hpp"

std::vector<std::string> scopeLookupTable =
{
  "exec",
  "if",
  "ef",
  "el",
  "compute"
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
  "DISC",
  "add",
  "subtract",
  "multiply",
  "divide"
};

std::vector<std::string> literalLookupTable;

std::vector<std::string> variableLookupTable;

bool grammarExists = false;
bool isQuoting = false;
unsigned argScope = 0;

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument)
{
  if (grammar != "")  //grammar pushed to arguments
  {
    std::cout << grammar << '\n';
    syntaxNode nextSyntax;
    nextSyntax._syntax = grammar;
    grammarExists = false;
    if (isArgument)
    {
      if (!grammarExists)
      {
        if (isQuoting)
        {
          std::cout << "literal arguments \n";
          literalLookupTable.push_back(grammar);
          nextSyntax._type = "literal";
          scopeStack.top()->_arguments.push_back(nextSyntax);
        }
        else
        {
          std::cout << "variable arguments1 \n";
          variableLookupTable.push_back(grammar);
          std::cout << "variable arguments2 \n";
          nextSyntax._type = "variable";
          std::cout << scopeStack.top()->_syntax << " variable arguments3 \n";
          scopeStack.top()->_arguments.push_back(nextSyntax);
          std::cout << "variable arguments4 \n";
        }
      }
      else
      {
        for (std::string _scope : scopeLookupTable)
        {
          std::cout << "scope arguments \n";
          if (_scope == grammar) {nextSyntax._type = "scope";grammarExists = true;scopeStack.top()->_arguments.push_back(nextSyntax);break;}
        }
        for (std::string _grammar : grammarLookupTable)
        {
          std::cout << "grammar arguments \n";
          if (_grammar == grammar) {nextSyntax._type = "grammar";grammarExists = true;scopeStack.top()->_arguments.push_back(nextSyntax);break;}
        }
      }
      //If grammar does not exist

    }
    else  //grammar pushed to scope
    {
      for (std::string _scope : scopeLookupTable)
      {
        std::cout << "scope scope \n";
        if (_scope == grammar) {nextSyntax._type = "scope";grammarExists = true;scopeStack.top()->_scope.push(nextSyntax); break;}
      }
      for (std::string _grammar : grammarLookupTable)
      {
        std::cout << "grammar scope \n";
        if (_grammar == grammar) {nextSyntax._type = "grammar";grammarExists = true;scopeStack.top()->_scope.push(nextSyntax);break;}
      }
      //if grammar does not exist

    }

    std::cout << grammar << '\n' << "Is argument? " << isArgument << '\n';
    scopeStack.push(&scopeStack.top()->_scope.back());  //set scope to the new scope.
  }
}

int scanSource(std::string& source)
{
  std::string keyword;
  bool isArgument = false;

  std::stack<syntaxNode*> scopeStack = {};
  scopeStack.push(new syntaxNode("global","global"));

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
    else if (!isQuoting)
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
          ++argScope;
          parseGrammar(scopeStack, keyword, isArgument);
          isArgument = true;
          keyword = "";
          break;
        case ')':
          --argScope;
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
          isArgument = true;
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
