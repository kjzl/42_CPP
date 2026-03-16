#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
    : _name("Default"), _signed(false), _gradeToSign(150), _gradeToExecute(150) {}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
    : _name(name), _signed(false), _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}

Form::Form(const Form &src)
    : _name(src._name), _signed(src._signed), _gradeToSign(src._gradeToSign),
      _gradeToExecute(src._gradeToExecute) {}

Form::~Form() {}

Form &Form::operator=(const Form &rhs) {
  if (this != &rhs)
    _signed = rhs._signed;
  return *this;
}

const std::string &Form::getName() const {
  return _name;
}

bool Form::getSigned() const {
  return _signed;
}

int Form::getGradeToSign() const {
  return _gradeToSign;
}

int Form::getGradeToExecute() const {
  return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat &b) {
  if (b.getGrade() > _gradeToSign)
    throw GradeTooLowException();
  _signed = true;
}

const char *Form::GradeTooHighException::what() const throw() {
  return "grade is too high";
}

const char *Form::GradeTooLowException::what() const throw() {
  return "grade is too low";
}

std::ostream &operator<<(std::ostream &o, const Form &f) {
  o << "Form " << f.getName() << ", signed: ";
  if (f.getSigned())
    o << "yes";
  else
    o << "no";
  o << ", grade to sign: " << f.getGradeToSign()
    << ", grade to execute: " << f.getGradeToExecute() << std::endl;
  return o;
}
