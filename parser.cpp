#include "parser.hpp"



void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument)
{
  //std::cout << scopeStack.top()->_syntax << '\n';
  if (grammar != "")  //grammar pushed to arguments
  {
    syntaxNode nextSyntax;
    nextSyntax._syntax = grammar;
    if (isArgument)
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar) scopeStack.top()->_arguments.push_back(nextSyntax);
        //std::cout << "DEBUG:: (parseGrammar::isArgument[0]) Parent : " <<  scopeStack.top()._syntax << '\n';
        //for (syntaxNode i : scopeStack.top()._arguments){std::cout << " - Argument : " << i._syntax << '\n';}
      }
      for (std::string _grammar : grammarLookupTable)
      {
        if (_grammar == grammar) scopeStack.top()->_arguments.push_back(nextSyntax);
        //std::cout << "DEBUG:: (parseGrammar::isArgument[1]) Parent : " <<  scopeStack.top()._syntax << '\n';
        //for (syntaxNode i : scopeStack.top()._arguments){std::cout << " - Argument : " << i._syntax << '\n';}
      }
    }
    else  //grammar pushed to scope
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar) {scopeStack.top()->_scope.push(nextSyntax); break;}
        //std::cout << "DEBUG:: (parseGrammar::isArgument[0]) Parent : " <<  scopeStack.top()._scope.front()._syntax << '\n';
        //for (syntaxNode i : scopeStack.top()._arguments){std::cout << " - Argument : " << i._syntax << '\n';}
      }
      for (std::string _grammar : grammarLookupTable)
      {

        if (_grammar == grammar) {scopeStack.top()->_scope.push(nextSyntax);
          //std::cout << scopeStack.top()->_scope.front()._syntax << " syntax pushed in scope of " << scopeStack.top()->_syntax << " \n"; break;}

        //std::cout << "DEBUG:: (parseGrammar::!isArgument[1]) Parent : " <<  scopeStack.top()._scope.front()._syntax << '\n';
        //for (syntaxNode i : scopeStack.top()._arguments){std::cout << " - Argument : " << i._syntax << '\n';}
      }
    }

    scopeStack.push(&scopeStack.top()->_scope.back());  //set scope to the new scope.
    //std::cout << "Parsed Grammar.\n";
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
        std::cout << scopeStack.top()->_syntax << '\n';
        scopeStack.pop();
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
        keyword = "";
        break;
      case '!':
        parseGrammar(scopeStack, keyword, isArgument);
        keyword = "";
        break;
      case ';':
        parseGrammar(scopeStack, keyword, isArgument);
        std::cout << scopeStack.top()->_syntax << '\n';
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
    //std::cout << " SCOPE : " << scopeStack.top()._syntax << '\n';
  }
  std::cout << "Compiled Successfully.\n";
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
  //std::cout << scopeStack.top()->_syntax << " - THIRD \n";
  itterateScope(*scopeStack.top());
  return 0;
}
