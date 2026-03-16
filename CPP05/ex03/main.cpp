#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <cstdlib>
#include <ctime>

int main() {
  std::srand(std::time(NULL));

  Intern someRandomIntern;
  AForm *form;

  std::cout << "=== Test: Robotomy Request ===" << std::endl;
  form = someRandomIntern.makeForm("robotomy request", "Bender");
  if (form) {
    Bureaucrat boss("Boss", 1);
    boss.signForm(*form);
    boss.executeForm(*form);
    delete form;
  }

  std::cout << "=== Test: Shrubbery Creation ===" << std::endl;
  form = someRandomIntern.makeForm("shrubbery creation", "garden");
  if (form) {
    Bureaucrat bob("Bob", 1);
    bob.signForm(*form);
    bob.executeForm(*form);
    delete form;
  }

  std::cout << "=== Test: Presidential Pardon ===" << std::endl;
  form = someRandomIntern.makeForm("presidential pardon", "Doctor Who");
  if (form) {
    Bureaucrat president("President", 1);
    president.signForm(*form);
    president.executeForm(*form);
    delete form;
  }

  std::cout << "=== Test: Unknown Form ===" << std::endl;
  form = someRandomIntern.makeForm("unknown form", "nobody");
  if (form)
    delete form;

  std::cout << "=== Test: Intern Copy Constructor ===" << std::endl;
  try {
    Intern intern1;
    Intern intern2(intern1);
    form = intern2.makeForm("presidential pardon", "Subject");
    if (form) {
      Bureaucrat boss("Boss", 1);
      boss.signForm(*form);
      boss.executeForm(*form);
      delete form;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Intern Assignment ===" << std::endl;
  try {
    Intern intern1;
    Intern intern2;
    intern2 = intern1;
    form = intern2.makeForm("robotomy request", "Clone");
    if (form) {
      Bureaucrat alice("Alice", 1);
      alice.signForm(*form);
      alice.executeForm(*form);
      delete form;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "=== Test: Multiple Forms Creation ===" << std::endl;
  {
    Intern intern;
    Bureaucrat boss("Boss", 1);

    form = intern.makeForm("shrubbery creation", "location1");
    if (form) {
      boss.signForm(*form);
      boss.executeForm(*form);
      delete form;
    }

    form = intern.makeForm("robotomy request", "subject1");
    if (form) {
      boss.signForm(*form);
      boss.executeForm(*form);
      delete form;
    }

    form = intern.makeForm("presidential pardon", "criminal1");
    if (form) {
      boss.signForm(*form);
      boss.executeForm(*form);
      delete form;
    }
  }

  return 0;
}
