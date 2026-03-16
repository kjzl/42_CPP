#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name) {
  if (grade < 1)
    throw GradeTooHighException();
  if (grade > 150)
    throw GradeTooLowException();
  _grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &src) : _name(src._name), _grade(src._grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &rhs) {
  if (this != &rhs)
    _grade = rhs._grade;
  return *this;
}

const std::string &Bureaucrat::getName() const {
  return _name;
}

int Bureaucrat::getGrade() const {
  return _grade;
}

void Bureaucrat::incrementGrade() {
  if (_grade <= 1)
    throw GradeTooHighException();
  _grade--;
}

void Bureaucrat::decrementGrade() {
  if (_grade >= 150)
    throw GradeTooLowException();
  _grade++;
}

void Bureaucrat::signForm(Form &f) {
  try {
    f.beSigned(*this);
    std::cout << _name << " signed " << f.getName() << std::endl;
  } catch (const std::exception &e) {
    std::cout << _name << " couldn't sign " << f.getName()
              << " because " << e.what() << std::endl;
  }
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
  return "grade is too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
  return "grade is too low";
}

std::ostream &operator<<(std::ostream &o, const Bureaucrat &b) {
  o << b.getName() << ", bureaucrat grade " << b.getGrade() << "." << std::endl;
  return o;
}
