#include "parser.hpp"

/* TODO:

 - implement functions.
 - garbage collection c++ and Jagged

 BUGS:

 - Variables must be referenced via string literal when writing to them.

*/

const std::string VERSION = "0.8.9";

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
    std::cout << " Jagged v" << VERSION << '\n';
    while(true)
    {
      std::cout << "§";
      getline(std::cin, input);
      scanSource(input);
    }
  }
}
