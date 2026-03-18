#include "RPN.hpp"

#include <cctype>
#include <list>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(RPN const &src) { *this = src; }

RPN::~RPN() {}

RPN &RPN::operator=(RPN const &rhs) {
  (void)rhs;
  return *this;
}

bool RPN::isOperatorToken(const std::string &token) {
  if (token.size() != 1)
    return false;
  return (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
          token[0] == '/');
}

bool RPN::isDigitToken(const std::string &token) {
  return (token.size() == 1 &&
          std::isdigit(static_cast<unsigned char>(token[0])));
}

long RPN::applyOperator(char op, long lhs, long rhs) {
  switch (op) {
  case '+':
    return lhs + rhs;
  case '-':
    return lhs - rhs;
  case '*':
    return lhs * rhs;
  case '/':
    if (rhs == 0)
      throw std::runtime_error("division by zero");
    return lhs / rhs;
  default:
    throw std::runtime_error("unknown operator");
  }
}

long RPN::evaluate(const std::string &expression) const {
  std::istringstream iss(expression);
  std::string token;
  std::list<long> stack;

  while (iss >> token) {
    if (isDigitToken(token)) {
      stack.push_back(static_cast<long>(token[0] - '0'));
    } else if (isOperatorToken(token)) {
      if (stack.size() < 2)
        throw std::runtime_error("not enough operands");

      long rhs = stack.back();
      stack.pop_back();
      long lhs = stack.back();
      stack.pop_back();

      long result = applyOperator(token[0], lhs, rhs);
      stack.push_back(result);
    } else {
      throw std::runtime_error("invalid token");
    }
  }

  if (stack.size() != 1)
    throw std::runtime_error("invalid expression");

  return stack.back();
}
