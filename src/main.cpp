#include "parser.hpp"

/* TODO:

 - *priority* Need to implement a private heap to store all data
 because c++ stack does not have enough memory to store everything.
 - make tokenizer more robust
 - add number tokenizer support so you dont have to put numbers in quotation marks

 BUGS:

 - Comments cause issues in tokenizer
 - Stack runs out of memory

*/

const std::string VERSION = "0.14.21";

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
    scanSource(getFileContent(argv[1], moduleContent), scopeStack);
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
      scanSource(getFileContent("NULL", input), scopeStack);
    }
  }
}
