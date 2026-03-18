#include "RPN.hpp"

#include <iostream>
#include <string>

static void printError() { std::cerr << "Error" << std::endl; }

int main(int argc, char **argv) {
  if (argc != 2) {
    printError();
    return 1;
  }

  try {
    RPN rpn;
    long result = rpn.evaluate(std::string(argv[1]));
    std::cout << result << std::endl;
  } catch (const std::exception &) {
    printError();
    return 1;
  }

  return 0;
}
