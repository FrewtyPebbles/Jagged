#include "parser.hpp"

/* TODO:

 - implement functions and variables.

 BUGS:

 - add a stack to parser.cpp to feed recursive argument scopes
 ex: thing(thing, (thing, thing));

 - Fix bug with 'free(): invalid pointer' with math

*/

const std::string VERSION = "0.3.6";

int main (int argc, char* argv[])
{
  std::string input;

  if (argc > 1)
  {
    std::ifstream sourceFile(argv[1], std::ifstream::in);
    std::stringstream source;
    source << sourceFile.rdbuf();
    input = source.str();
    scanSource(input);
  }
  else
  {
    std::cout << " - Jagged - v:" << VERSION << '\n';
    while(true)
    {
      std::cout << "<|";
      std::cin >> input;
      scanSource(input);
    }
  }
}
