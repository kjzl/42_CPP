#include "easyfind.hpp"
#include <deque>
#include <iostream>
#include <list>
#include <vector>

template <typename T>
static void testFind(const T &container, int value) {
  try {
    typename T::const_iterator it = easyfind(container, value);
    std::cout << "Found " << value << " at position "
              << std::distance(container.begin(), it) << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Looking for " << value << ": " << e.what() << std::endl;
  }
}

int main() {
  std::cout << "--- vector<int> ---" << std::endl;
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(42);
  vec.push_back(7);
  vec.push_back(-3);
  vec.push_back(42);

  testFind(vec, 42);
  testFind(vec, 7);
  testFind(vec, 100);

  std::cout << std::endl;
  std::cout << "--- list<int> ---" << std::endl;
  std::list<int> lst;
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);

  testFind(lst, 20);
  testFind(lst, 99);

  std::cout << std::endl;
  std::cout << "--- deque<int> ---" << std::endl;
  std::deque<int> dq;
  dq.push_back(5);
  dq.push_back(15);
  dq.push_back(25);

  testFind(dq, 15);
  testFind(dq, 0);

  std::cout << std::endl;
  std::cout << "--- empty vector ---" << std::endl;
  std::vector<int> empty;
  testFind(empty, 1);

  return 0;
}
