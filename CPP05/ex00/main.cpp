#include "Bureaucrat.hpp"

int main() {
  std::cout << "=== Test: Valid Bureaucrat ===" << std::endl;
  try {
    Bureaucrat bob("Bob", 42);
    std::cout << bob;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Grade Too High (0) ===" << std::endl;
  try {
    Bureaucrat high("High", 0);
    std::cout << high;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Grade Too Low (151) ===" << std::endl;
  try {
    Bureaucrat low("Low", 151);
    std::cout << low;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Increment ===" << std::endl;
  try {
    Bureaucrat alice("Alice", 2);
    std::cout << alice;
    alice.incrementGrade();
    std::cout << alice;
    alice.incrementGrade();
    std::cout << alice;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Decrement ===" << std::endl;
  try {
    Bureaucrat charlie("Charlie", 149);
    std::cout << charlie;
    charlie.decrementGrade();
    std::cout << charlie;
    charlie.decrementGrade();
    std::cout << charlie;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Copy ===" << std::endl;
  try {
    Bureaucrat orig("Original", 50);
    Bureaucrat copy(orig);
    std::cout << "Original: " << orig;
    std::cout << "Copy: " << copy;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Assignment ===" << std::endl;
  try {
    Bureaucrat a("Alice", 75);
    Bureaucrat b("Bob", 25);
    std::cout << "Before assignment - A: " << a;
    std::cout << "Before assignment - B: " << b;
    a = b;
    std::cout << "After assignment - A: " << a;
    std::cout << "After assignment - B: " << b;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Boundary Grade 1 ===" << std::endl;
  try {
    Bureaucrat best("Best", 1);
    std::cout << best;
    best.incrementGrade();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Boundary Grade 150 ===" << std::endl;
  try {
    Bureaucrat worst("Worst", 150);
    std::cout << worst;
    worst.decrementGrade();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
