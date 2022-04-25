#include "parser.hpp"

//TOKENIZER

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
  "index",
  "add",
  "concatenate",
  "return",
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

bool isFloat( std::string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

void parseGrammar(std::stack<syntaxNode*>& scopeStack, std::string grammar, bool isArgument)
{
  if (grammar != "")  //grammar pushed to arguments
  {
    syntaxNode nextSyntax;
    nextSyntax._syntax = grammar;
    nextSyntax._parent = scopeStack.top();
    grammarExists = false;
    if (isQuoting || isFloat( grammar ))
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
        nextSyntax._type = "functionCall";
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

int scanSource(std::string source, std::stack<syntaxNode*> & scopeStack)
{
  std::string keyword;
  bool isArgument = false;
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
        case '\n':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case ' ':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '\t':
          parseGrammar(scopeStack, keyword, isArgument);
          keyword = "";
          break;
        case '\r':
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
  return 0;
}

std::string getFileContent(std::string fileContent)
{
  std::string Keyword;
  std::stringstream Content;
  bool isReading = false;
  //std::cout << fileContent << "<-CONTENT\n";
  for(char fileCharacter : fileContent)
  {
    //std::cout << fileCharacter << " < - char\n";
    if (isReading == true)
    {
      Content << std::string( 1, fileCharacter );
    }
    else if (fileCharacter == '\n' && (Keyword == "STARTMOD" || Keyword == "ENDINCLUDES" || Keyword == "ENDINC" || Keyword == "INCLUDES") && isReading == false)
    {
      isReading = true;
      Keyword = "";
    }
    else if (fileCharacter == '\n' && isReading == false && Keyword != "" && Keyword != "\n")
    {
      //std::cout << Keyword << "<-file\n";
      std::string moduleContent;
      std::stringstream source;
      try{
        std::ifstream moduleFile(Keyword + ".jag", std::ifstream::in);
        moduleFile.exceptions ( std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit );
        source << moduleFile.rdbuf();
        moduleFile.close();
        moduleContent = "\n" + source.str();
        //std::cout << moduleContent;
        Content << "\n" << getFileContent(moduleContent) << "\n";

      }
      catch(std::exception const& e)
      {
        std::cout << "\n (PREPROCESSOR) !ERROR! > MODULE NOT FOUND : " << Keyword << ".jag\nMake sure your file path is relative to the compiler and didnt include an extension!\n\n";
      }
      Keyword = "";
    }
    if (fileCharacter != '\r' && fileCharacter != '\n')
    Keyword += fileCharacter;
  }
  //std::cout << Content.str();
  return Content.str();
}
