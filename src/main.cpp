#include "parser.hpp"

/* TODO:

 - make modules relative to "rootModule"/../"relative module path"
 - make tokenizer more robust
 - add number tokenizer support so you dont have to put numbers in quotation marks

 BUGS:

 - Comments cause issues in tokenizer
 - User function arguments parse more than once
 as an standard library function argument.

*/

const std::string VERSION = "0.13.21";

int main (int argc, char* argv[])
{
  std::string input;

  if (argc > 1)
  {
    std::stack<syntaxNode*> scopeStack = {};
    scopeStack.push(new syntaxNode("global","global","global"));
    std::string moduleContent;
    std::ifstream sourceFile(argv[1], std::ifstream::in);
    std::stringstream source;
    source << sourceFile.rdbuf();
    sourceFile.close();
    moduleContent = "\n" + source.str();
    //std::cout << getFileContent(moduleContent);
    scanSource(getFileContent(moduleContent), scopeStack);
  }
  else
  {
    std::cout << " Jagged v" << VERSION << '\n';
    while(true)
    {
      std::cout << "§";
      getline(std::cin, input);
      input = "\nSTARTMOD\n" + input;
      std::stack<syntaxNode*> scopeStack = {};
      scopeStack.push(new syntaxNode("global","global","global"));
      //std::cout << getFileContent(input);
      scanSource(getFileContent(input), scopeStack);
    }
  }
}
