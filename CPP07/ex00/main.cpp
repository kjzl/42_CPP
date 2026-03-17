#include "whatever.hpp"

#include <iostream>
#include <string>

int main(void) {
  int a = 2;
  int b = 3;

  ::swap(a, b);
  std::cout << "a = " << a << ", b = " << b << std::endl;
  std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
  std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

  std::string c = "chaine1";
  std::string d = "chaine2";

  ::swap(c, d);
  std::cout << "c = " << c << ", d = " << d << std::endl;
  std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
  std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

  // Test "return second if equal"
  int x = 5;
  int y = 5;
  std::cout << std::endl;
  std::cout << "x = " << x << ", y = " << y << std::endl;
  std::cout << "min returns second: " << (&::min(x, y) == &y) << std::endl;
  std::cout << "max returns second: " << (&::max(x, y) == &y) << std::endl;

  return 0;
}
