#include "Array.hpp"

#include <iostream>
#include <string>

int main(void) {
  // Default constructor
  Array<int> empty;
  std::cout << "Empty array size: " << empty.size() << std::endl;

  // Parameterized constructor - value initialization
  Array<int> nums(5);
  std::cout << "Default-initialized ints: ";
  for (unsigned int i = 0; i < nums.size(); i++)
    std::cout << nums[i] << " ";
  std::cout << std::endl;

  // Modify elements
  for (unsigned int i = 0; i < nums.size(); i++)
    nums[i] = static_cast<int>(i * 10);
  std::cout << "After assignment: ";
  for (unsigned int i = 0; i < nums.size(); i++)
    std::cout << nums[i] << " ";
  std::cout << std::endl;

  // Copy constructor - deep copy
  Array<int> copy(nums);
  copy[0] = 999;
  std::cout << "Original[0]: " << nums[0] << ", Copy[0]: " << copy[0] << std::endl;

  // Assignment operator - deep copy
  Array<int> assigned;
  assigned = nums;
  assigned[1] = 888;
  std::cout << "Original[1]: " << nums[1] << ", Assigned[1]: " << assigned[1] << std::endl;

  // Self-assignment
  nums = nums;
  std::cout << "After self-assign[0]: " << nums[0] << std::endl;

  // Out of bounds
  try {
    nums[100] = 42;
  } catch (const std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  // Out of bounds on empty array
  try {
    empty[0] = 1;
  } catch (const std::exception &e) {
    std::cout << "Exception on empty: " << e.what() << std::endl;
  }

  // Const access
  const Array<int> constArr(nums);
  std::cout << "Const access[2]: " << constArr[2] << std::endl;

  try {
    (void)constArr[100];
  } catch (const std::exception &e) {
    std::cout << "Const exception: " << e.what() << std::endl;
  }

  // String type
  Array<std::string> strs(3);
  strs[0] = "hello";
  strs[1] = "world";
  strs[2] = "!";
  std::cout << "Strings: ";
  for (unsigned int i = 0; i < strs.size(); i++)
    std::cout << strs[i] << " ";
  std::cout << std::endl;

  // Copy string array and verify independence
  Array<std::string> strCopy(strs);
  strCopy[0] = "goodbye";
  std::cout << "Original str[0]: " << strs[0] << ", Copy str[0]: " << strCopy[0] << std::endl;

  return 0;
}
