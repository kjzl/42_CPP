#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
public:
  static void convert(const std::string &literal);

private:
  ScalarConverter();
  ScalarConverter(const ScalarConverter &src);
  ~ScalarConverter();

  ScalarConverter &operator=(const ScalarConverter &rhs);
};

#endif
