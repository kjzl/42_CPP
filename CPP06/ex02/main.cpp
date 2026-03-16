#include "identify.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::srand(std::time(NULL));

  for (int i = 0; i < 10; i++) {
    Base *obj = generate();

    std::cout << "Pointer: ";
    identify(obj);

    std::cout << "Reference: ";
    identify(*obj);

    delete obj;
    std::cout << std::endl;
  }

  return 0;
}
