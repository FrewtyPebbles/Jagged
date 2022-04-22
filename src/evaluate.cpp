#include "parser.hpp"
std::string evaluateToken(std::string source)
{
  std::stack<std::string[2]> numberPair;
  std::string currentPair[2];
  bool rightSide = false;
  for (char character : source)
  {
    if (!rightSide)
    switch (character) {
      case '(':
        break;
      case ')':
        break;
      case '*':
        break;
      case '/':
        break;
      case '+':
        break;
      case '-':
        break;
      default:
        currentPair[rightSide] += character;
    }
  }
}
//USE {pmdas}
//()
std::string evaluateParentheses(std::string)
{

}

std::string evaluateMultiplication(std::string)
{

}
std::string evaluateDivision(std::string)
{

}
std::string evaluateAddition(std::string)
{

}
std::string evaluateSubtraction(std::string)
{

}
