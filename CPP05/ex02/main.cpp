#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <cstdlib>
#include <ctime>

int main() {
  std::srand(std::time(NULL));

  std::cout << "=== Test: ShrubberyCreationForm ===" << std::endl;
  try {
    Bureaucrat bob("Bob", 130);
    ShrubberyCreationForm shrub("home");
    std::cout << shrub;
    bob.signForm(shrub);
    bob.executeForm(shrub);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: RobotomyRequestForm ===" << std::endl;
  try {
    Bureaucrat alice("Alice", 40);
    RobotomyRequestForm robo("Bender");
    std::cout << robo;
    alice.signForm(robo);
    alice.executeForm(robo);
    alice.executeForm(robo);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: PresidentialPardonForm ===" << std::endl;
  try {
    Bureaucrat president("President", 1);
    PresidentialPardonForm pardon("Doctor Who");
    std::cout << pardon;
    president.signForm(pardon);
    president.executeForm(pardon);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Execute unsigned form ===" << std::endl;
  try {
    Bureaucrat boss("Boss", 1);
    PresidentialPardonForm pardon("Ford Prefect");
    boss.executeForm(pardon);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Grade too low to execute ===" << std::endl;
  try {
    Bureaucrat boss("Boss", 1);
    Bureaucrat intern("Intern", 150);
    PresidentialPardonForm pardon("Trillian");
    boss.signForm(pardon);
    intern.executeForm(pardon);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Grade too low to sign ===" << std::endl;
  try {
    Bureaucrat intern("Intern", 150);
    RobotomyRequestForm robo("Marvin");
    intern.signForm(robo);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Form Copy Constructor ===" << std::endl;
  try {
    Bureaucrat boss("Boss", 1);
    ShrubberyCreationForm orig("garden1");
    ShrubberyCreationForm copy(orig);
    boss.signForm(copy);
    boss.executeForm(copy);
    std::cout << "Original: " << orig;
    std::cout << "Copy: " << copy;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Form Assignment ===" << std::endl;
  try {
    Bureaucrat boss("Boss", 1);
    RobotomyRequestForm f1("target1");
    RobotomyRequestForm f2("target2");
    boss.signForm(f1);
    std::cout << "F1 signed before assignment: " << f1.getSigned() << std::endl;
    std::cout << "F2 signed before assignment: " << f2.getSigned() << std::endl;
    f2 = f1;
    std::cout << "F2 signed after assignment: " << f2.getSigned() << std::endl;
    boss.executeForm(f2);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Multiple RobotomyRequestForm Executions ===" << std::endl;
  try {
    Bureaucrat boss("Boss", 1);
    RobotomyRequestForm robo("Subject");
    boss.signForm(robo);
    boss.executeForm(robo);
    boss.executeForm(robo);
    boss.executeForm(robo);
    boss.executeForm(robo);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
