#include "parser.hpp"

/* TODO:

 - implement functions and variables.

 - possibly append variable names to grammarLookupTable to parse them better after
 instantiation.

 BUGS:

 - variable function causes a segmentation fault or bad_alloc.

*/

const std::string VERSION = "0.2.5";

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
