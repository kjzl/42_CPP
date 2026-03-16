#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
public:
  Form();
  Form(const std::string &name, int gradeToSign, int gradeToExecute);
  Form(const Form &src);
  ~Form();

  Form &operator=(const Form &rhs);

  const std::string &getName() const;
  bool getSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;

  void beSigned(const Bureaucrat &b);

  class GradeTooHighException : public std::exception {
  public:
    const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    const char *what() const throw();
  };

private:
  const std::string _name;
  bool _signed;
  const int _gradeToSign;
  const int _gradeToExecute;
};

std::ostream &operator<<(std::ostream &o, const Form &f);

#endif
