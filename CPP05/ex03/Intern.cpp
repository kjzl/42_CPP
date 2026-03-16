#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

static AForm *createShrubbery(const std::string &target) {
  return new ShrubberyCreationForm(target);
}

static AForm *createRobotomy(const std::string &target) {
  return new RobotomyRequestForm(target);
}

static AForm *createPresidential(const std::string &target) {
  return new PresidentialPardonForm(target);
}

Intern::Intern() {}

Intern::Intern(const Intern &src) {
  (void)src;
}

Intern::~Intern() {}

Intern &Intern::operator=(const Intern &rhs) {
  (void)rhs;
  return *this;
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) {
  const std::string names[] = {
    "shrubbery creation",
    "robotomy request",
    "presidential pardon"
  };

  AForm *(*creators[])(const std::string &) = {
    &createShrubbery,
    &createRobotomy,
    &createPresidential
  };

  for (int i = 0; i < 3; i++) {
    if (names[i] == name) {
      std::cout << "Intern creates " << name << std::endl;
      return creators[i](target);
    }
  }
  std::cout << "Intern couldn't find form: " << name << std::endl;
  return NULL;
}
