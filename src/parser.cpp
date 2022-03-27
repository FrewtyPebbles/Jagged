#include "parser.hpp"

const std::string scopeLookupTable[4] =
{
  "exec",
  "if",
  "ef",
  "el"
};
std::string grammarLookupTable[8] =
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

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument)
{
  if (grammar != "")  //grammar pushed to arguments
  {
    syntaxNode nextSyntax;
    nextSyntax._syntax = grammar;
    if (isArgument)
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar) {scopeStack.top()->_arguments.push_back(nextSyntax);break;}
      }
      for (std::string _grammar : grammarLookupTable)
      {
        if (_grammar == grammar) {scopeStack.top()->_arguments.push_back(nextSyntax);break;}
      }
      //If grammar does not exist

    }
    else  //grammar pushed to scope
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar) {scopeStack.top()->_scope.push(nextSyntax); break;}
      }
      for (std::string _grammar : grammarLookupTable)
      {
        if (_grammar == grammar) {scopeStack.top()->_scope.push(nextSyntax);break;}
      }
      //if grammar does not exist

    }
    scopeStack.push(&scopeStack.top()->_scope.back());  //set scope to the new scope.
  }
}

int scanSource(std::string& source)
{
  std::string keyword;
  bool isArgument = false;

  std::stack<syntaxNode*> scopeStack = {};
  scopeStack.push(new syntaxNode("global"));

  for(char character : source)
  {
    switch (character) {
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
        std::cout << scopeStack.top()->_syntax << '\n';
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
        std::cout << scopeStack.top()->_syntax << '\n';
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
  std::cout << "Compiled Successfully.\n";
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
