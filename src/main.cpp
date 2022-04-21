#include "parser.hpp"

/* TODO:

 - implement modules
 - make tokenizer more robust
 - add number tokenizer support so you dont have to put numbers in quotation marks

 BUGS:

 - Comments cause issues in tokenizer
 - Modules have ordering bug when multiple calls in certain order from a main file.

*/

const std::string VERSION = "0.12.18";

int main (int argc, char* argv[])
{
  std::string input;

  if (argc > 1)
  {
    std::ifstream sourceFile(argv[1], std::ifstream::in);
    std::stringstream source;
    source << sourceFile.rdbuf();
    input = "\n" + source.str();
    std::stack<syntaxNode*> scopeStack = {};
    scopeStack.push(new syntaxNode("global","global","global"));
    scanSource(input, scopeStack);
  }
  else
  {
    std::cout << " Jagged v" << VERSION << '\n';
    while(true)
    {
      std::cout << "§";
      getline(std::cin, input);
      input = "\n" + input;
      std::stack<syntaxNode*> scopeStack = {};
      scopeStack.push(new syntaxNode("global","global","global"));
      scanSource(input, scopeStack);
    }
  }
}
