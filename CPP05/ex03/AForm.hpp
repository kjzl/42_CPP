#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class AForm {
public:
  AForm();
  AForm(const std::string &name, int gradeToSign, int gradeToExecute);
  AForm(const AForm &src);
  virtual ~AForm();

  AForm &operator=(const AForm &rhs);

  const std::string &getName() const;
  bool getSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;

  void beSigned(const Bureaucrat &b);
  void execute(const Bureaucrat &executor) const;

  class GradeTooHighException : public std::exception {
  public:
    const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    const char *what() const throw();
  };

  class FormNotSignedException : public std::exception {
  public:
    const char *what() const throw();
  };

private:
  const std::string _name;
  bool _signed;
  const int _gradeToSign;
  const int _gradeToExecute;

  virtual void doExecute() const = 0;
};

std::ostream &operator<<(std::ostream &o, const AForm &f);

#endif
