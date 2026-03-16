#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
    : _name("Default"), _signed(false), _gradeToSign(150), _gradeToExecute(150) {}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
    : _name(name), _signed(false), _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}

AForm::AForm(const AForm &src)
    : _name(src._name), _signed(src._signed), _gradeToSign(src._gradeToSign),
      _gradeToExecute(src._gradeToExecute) {}

AForm::~AForm() {}

AForm &AForm::operator=(const AForm &rhs) {
  if (this != &rhs)
    _signed = rhs._signed;
  return *this;
}

const std::string &AForm::getName() const {
  return _name;
}

bool AForm::getSigned() const {
  return _signed;
}

int AForm::getGradeToSign() const {
  return _gradeToSign;
}

int AForm::getGradeToExecute() const {
  return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat &b) {
  if (b.getGrade() > _gradeToSign)
    throw GradeTooLowException();
  _signed = true;
}

void AForm::execute(const Bureaucrat &executor) const {
  if (!_signed)
    throw FormNotSignedException();
  if (executor.getGrade() > _gradeToExecute)
    throw GradeTooLowException();
  doExecute();
}

const char *AForm::GradeTooHighException::what() const throw() {
  return "grade is too high";
}

const char *AForm::GradeTooLowException::what() const throw() {
  return "grade is too low";
}

const char *AForm::FormNotSignedException::what() const throw() {
  return "form is not signed";
}

std::ostream &operator<<(std::ostream &o, const AForm &f) {
  o << "Form " << f.getName() << ", signed: ";
  if (f.getSigned())
    o << "yes";
  else
    o << "no";
  o << ", grade to sign: " << f.getGradeToSign()
    << ", grade to execute: " << f.getGradeToExecute() << std::endl;
  return o;
}
