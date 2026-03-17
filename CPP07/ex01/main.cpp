#include "iter.hpp"

#include <iostream>
#include <string>

template <typename T>
void print(const T &x) {
  std::cout << x << std::endl;
}

template <typename T>
void increment(T &x) {
  x++;
}

int main(void) {
  int intArr[] = {1, 2, 3, 4, 5};
  size_t intLen = sizeof(intArr) / sizeof(intArr[0]);

  std::cout << "Int array:" << std::endl;
  ::iter(intArr, intLen, print<int>);

  std::cout << "After increment:" << std::endl;
  ::iter(intArr, intLen, increment<int>);
  ::iter(intArr, intLen, print<int>);

  std::string strArr[] = {"hello", "world", "foo"};
  size_t strLen = sizeof(strArr) / sizeof(strArr[0]);

  std::cout << "String array:" << std::endl;
  ::iter(strArr, strLen, print<std::string>);

  // Test with const array
  const double constArr[] = {1.1, 2.2, 3.3};
  size_t constLen = sizeof(constArr) / sizeof(constArr[0]);

  std::cout << "Const double array:" << std::endl;
  ::iter(constArr, constLen, print<double>);

  // Test with empty array
  std::cout << "Empty array (no output):" << std::endl;
  ::iter(intArr, static_cast<size_t>(0), print<int>);

  return 0;
}
