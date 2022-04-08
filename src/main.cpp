#include "parser.hpp"

/* TODO:

 - implement functions.

 BUGS:

-=***=- elif still does not work, neither does else.

-=***=- user functions return at the end of their scope without
a return keyword.

*/

const std::string VERSION = "0.9.14";

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
