#include "parser.hpp"

/* TODO:

 - implement functions.

 BUGS:

 - inside exec(with arguments) STL functions and elif
 only works inside an if statement

 - User functions call arguments more than once

*/

const std::string VERSION = "0.10.17";

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
