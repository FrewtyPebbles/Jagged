#include "parser.hpp"

/* TODO:

 - implement functions.

 BUGS:

*/

const std::string VERSION = "0.10.16";

int main (int argc, char* argv[])
{
  std::string input;

  if (argc > 1)
  {
    std::ifstream sourceFile(argv[1], std::ifstream::in);
    std::stringstream source;
    source << sourceFile.rdbuf();
    input = "\n" + source.str();
    scanSource(input);
  }
  else
  {
    std::cout << " Jagged v" << VERSION << '\n';
    while(true)
    {
      std::cout << "§";
      getline(std::cin, input);
      input = "\n" + input;
      scanSource(input);
    }
  }
}
