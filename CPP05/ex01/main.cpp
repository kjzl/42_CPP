#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
  std::cout << "=== Test: Create valid Form ===" << std::endl;
  try {
    Form f("Tax Return", 50, 25);
    std::cout << f;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Form with invalid grades ===" << std::endl;
  try {
    Form f("Bad Form", 0, 25);
    std::cout << f;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  try {
    Form f("Bad Form", 50, 151);
    std::cout << f;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Sign Form (success) ===" << std::endl;
  try {
    Bureaucrat bob("Bob", 40);
    Form f("Tax Return", 50, 25);
    bob.signForm(f);
    std::cout << f;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Sign Form (failure) ===" << std::endl;
  try {
    Bureaucrat intern("Intern", 100);
    Form f("Tax Return", 50, 25);
    intern.signForm(f);
    std::cout << f;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Sign already signed Form ===" << std::endl;
  try {
    Bureaucrat boss("Boss", 1);
    Form f("Tax Return", 50, 25);
    boss.signForm(f);
    boss.signForm(f);
    std::cout << f;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Form Copy Constructor ===" << std::endl;
  try {
    Form original("Original Form", 60, 40);
    Form copy(original);
    std::cout << "Original: " << original;
    std::cout << "Copy: " << copy;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Form Assignment ===" << std::endl;
  try {
    Bureaucrat alice("Alice", 20);
    Form f1("Form 1", 50, 25);
    Form f2("Form 2", 100, 50);
    alice.signForm(f1);
    std::cout << "F1 before assignment: " << f1;
    std::cout << "F2 before assignment: " << f2;
    f2 = f1;
    std::cout << "F2 after assignment: " << f2;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Boundary Grades (1 and 150) ===" << std::endl;
  try {
    Form best("Best Form", 1, 1);
    Form worst("Worst Form", 150, 150);
    std::cout << "Best: " << best;
    std::cout << "Worst: " << worst;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
