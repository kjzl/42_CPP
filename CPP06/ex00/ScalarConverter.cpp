#include "ScalarConverter.hpp"
#include <cctype>
#include <climits>
#include <cmath>
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <iomanip>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &src) { (void)src; }
ScalarConverter::~ScalarConverter() {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs) { (void)rhs; return *this; }

enum LiteralType {
  TYPE_CHAR,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_DOUBLE,
  TYPE_PSEUDO,
  TYPE_INVALID
};

static bool isPseudoLiteral(const std::string &s) {
  return s == "nan" || s == "nanf"
    || s == "+inf" || s == "-inf"
    || s == "+inff" || s == "-inff"
    || s == "inf" || s == "inff";
}

static LiteralType detectType(const std::string &s) {
  if (s.empty())
    return TYPE_INVALID;

  if (isPseudoLiteral(s))
    return TYPE_PSEUDO;

  if (s.length() == 1 && !std::isdigit(s[0]))
    return TYPE_CHAR;

  char *end;
  errno = 0;
  std::strtol(s.c_str(), &end, 10);
  if (*end == '\0' && errno != ERANGE)
    return TYPE_INT;

  std::strtod(s.c_str(), &end);
  if (*end == 'f' && *(end + 1) == '\0')
    return TYPE_FLOAT;
  if (*end == '\0')
    return TYPE_DOUBLE;

  return TYPE_INVALID;
}

static void printChar(double value, bool impossible) {
  std::cout << "char: ";
  if (impossible || std::isnan(value) || std::isinf(value)
      || value < 0 || value > 127)
    std::cout << "impossible" << std::endl;
  else if (!std::isprint(static_cast<int>(value)))
    std::cout << "Non displayable" << std::endl;
  else
    std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
}

static void printInt(double value, bool impossible) {
  std::cout << "int: ";
  if (impossible || std::isnan(value) || std::isinf(value)
      || value > static_cast<double>(INT_MAX)
      || value < static_cast<double>(INT_MIN))
    std::cout << "impossible" << std::endl;
  else
    std::cout << static_cast<int>(value) << std::endl;
}

static void printFloat(double value, bool impossible) {
  std::cout << "float: ";
  if (impossible) {
    std::cout << "impossible" << std::endl;
    return;
  }
  float f = static_cast<float>(value);
  if (!std::isinf(f) && !std::isnan(f)
      && f >= static_cast<float>(INT_MIN) && f <= static_cast<float>(INT_MAX)
      && f == static_cast<int>(f))
    std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
  else
    std::cout << f << "f" << std::endl;
}

static void printDouble(double value, bool impossible) {
  std::cout << "double: ";
  if (impossible) {
    std::cout << "impossible" << std::endl;
    return;
  }
  if (!std::isinf(value) && !std::isnan(value)
      && value >= static_cast<double>(INT_MIN) && value <= static_cast<double>(INT_MAX)
      && value == static_cast<int>(value))
    std::cout << std::fixed << std::setprecision(1) << value << std::endl;
  else
    std::cout << value << std::endl;
}

static void handlePseudo(const std::string &s) {
  double value;
  if (s == "nan" || s == "nanf")
    value = std::strtod("nan", NULL);
  else if (s == "+inf" || s == "+inff" || s == "inf" || s == "inff")
    value = std::strtod("inf", NULL);
  else
    value = std::strtod("-inf", NULL);

  printChar(value, true);
  printInt(value, true);
  printFloat(value, false);
  printDouble(value, false);
}

void ScalarConverter::convert(const std::string &literal) {
  LiteralType type = detectType(literal);

  if (type == TYPE_INVALID) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
    return;
  }

  if (type == TYPE_PSEUDO) {
    handlePseudo(literal);
    return;
  }

  double value;

  if (type == TYPE_CHAR) {
    value = static_cast<double>(literal[0]);
  } else if (type == TYPE_FLOAT) {
    value = static_cast<double>(std::strtof(literal.c_str(), NULL));
  } else {
    value = std::strtod(literal.c_str(), NULL);
  }

  printChar(value, false);
  printInt(value, false);
  printFloat(value, false);
  printDouble(value, false);
}
