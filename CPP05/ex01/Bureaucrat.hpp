#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <iostream>
#include <string>

class Form;

class Bureaucrat {
public:
  Bureaucrat();
  Bureaucrat(const std::string &name, int grade);
  Bureaucrat(const Bureaucrat &src);
  ~Bureaucrat();

  Bureaucrat &operator=(const Bureaucrat &rhs);

  const std::string &getName() const;
  int getGrade() const;

  void incrementGrade();
  void decrementGrade();

  void signForm(Form &f);

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
  int _grade;
};

std::ostream &operator<<(std::ostream &o, const Bureaucrat &b);

#endif
