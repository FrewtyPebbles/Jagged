#include "parser.hpp"

std::vector<std::string> scopeLookupTable =
{
  "exec",
  "if",
  "elif",
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
  "DISC",
  "set",
  "add",
  "subtract",
  "multiply",
  "divide",
  "equal"
};

std::vector<std::string> literalLookupTable;

std::vector<std::string> variableLookupTable;

bool grammarExists = false;
bool isQuoting = false;
bool isComment = false;
unsigned argScope = 0;

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument)
{
  if (grammar != "")  //grammar pushed to arguments
  {
    syntaxNode nextSyntax;
    nextSyntax._syntax = grammar;
    grammarExists = false;
    if (isQuoting)
    {
      literalLookupTable.push_back(grammar);
      nextSyntax._type = "literal";

      scopeStack.top()->_arguments.push_back(nextSyntax);
    }
    else if (isArgument)
    {
        for (std::string _scope : scopeLookupTable)
        {
          if (_scope == grammar)
          {
            nextSyntax._type = "scope";grammarExists = true;scopeStack.top()->_arguments.push_back(nextSyntax);break;
          }
        }
        for (std::string _grammar : grammarLookupTable)
        {
          if (_grammar == grammar)
          {
            nextSyntax._type = "grammar";grammarExists = true;scopeStack.top()->_arguments.push_back(nextSyntax);break;
          }
        }
      //If grammar does not exist

    }
    else  //grammar pushed to scope
    {
      for (std::string _scope : scopeLookupTable)
      {
        if (_scope == grammar)
        {
          nextSyntax._type = "scope";grammarExists = true;scopeStack.top()->_scope.push_back(nextSyntax); break;
        }
      }
      for (std::string _grammar : grammarLookupTable)
      {
        if (_grammar == grammar)
        {
          nextSyntax._type = "grammar";grammarExists = true;scopeStack.top()->_scope.push_back(nextSyntax);break;
        }
      }
      //if grammar does not exist

    }
    if (!grammarExists && !isQuoting)
    {
      if (isArgument)
      {
        variableLookupTable.push_back(grammar);
        nextSyntax._type = "variable";
        scopeStack.top()->_arguments.push_back(nextSyntax);
      }
      else
      {
        variableLookupTable.push_back(grammar);
        nextSyntax._type = "scope";
        scopeStack.top()->_scope.push_back(nextSyntax);
      }
    }

    if (isArgument == false)
    {
      scopeStack.push(&scopeStack.top()->_scope.back());  //set scope to the new scope.
    }
    else
    {
      scopeStack.push(&scopeStack.top()->_arguments.back());  //set scope to the new scope.
    }
  }
}

int scanSource(std::string& source)
{
  std::string keyword;
  bool isArgument = false;

  std::stack<syntaxNode*> scopeStack = {};
  scopeStack.push(new syntaxNode("global","global","global"));
  char lastChar;
  for(char character : source)
  {
    if (lastChar == '`')//ESCAPES
    {
      if (character == 'n') keyword += '\n';
      else if (character == 't') keyword += '\t';
      else if (character == 'b') keyword += '\b';
      else if (character == 'r') keyword += '\r';
      else if (character == 'v') keyword += '\v';
      else if (character == 'a') keyword += '\a';
      else if (character == 'f') keyword += '\f';
      lastChar = character;
      continue;
    }
    if (character == '#' && !isQuoting && !isComment)
    {
      isComment = true;
    }
    else if ((character == '\n') && isComment && !isQuoting)
    {
      isComment = false;
    }
    if (character == '"' && !isComment)
    {
      //check quoting.
      if (isQuoting == true)
      {
        //push quote
        parseGrammar(scopeStack, keyword, isArgument);
        keyword = "";
      }
      isQuoting = !isQuoting;
    }
    else if (!isQuoting && !isComment)
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
          scopeStack.pop();
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
    else if (character != '"' && character != '`' && !isComment)
    {
      keyword += character;
    }
    if (!isComment)lastChar = character;
  }
  std::vector<syntaxNode> defaultVec = {};
  itterateScope(*scopeStack.top(), defaultVec);
  scopeStack.pop();
  return 0;
}
