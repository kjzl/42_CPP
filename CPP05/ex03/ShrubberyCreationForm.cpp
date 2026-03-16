#include "ShrubberyCreationForm.hpp"

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), _target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src)
    : AForm(src), _target(src._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs) {
  if (this != &rhs) {
    AForm::operator=(rhs);
    _target = rhs._target;
  }
  return *this;
}

// https://ascii.co.uk/art/tree
void ShrubberyCreationForm::doExecute() const {
  std::ofstream file((_target + "_shrubbery").c_str());
  if (!file.is_open()) {
    throw std::runtime_error("could not open file");
  }

  const char *art[] = {
    "               ,@@@@@@@,",
    "       ,,,.   ,@@@@@@/@@,  .oo8888o.",
    "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o",
    "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88\'",
    "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888\'",
    "   %&&%/ %&%%&&@@\\ V /@@\' `88\\8 `/88\'",
    "   `&%\\ ` /%&\'    |.|        \\ \'|8\'",
    "       |o|        | |         | |",
    "       |.|        | |         | |",
    "jgs \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_"
  };

  for (int i = 0; i < static_cast<int>(sizeof(art) / sizeof(art[0])); ++i) {
    file << art[i] << std::endl;
  }

  file.close();
}

