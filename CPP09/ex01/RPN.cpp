#include "RPN.hpp"

#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN &src) {
  *this = src;
}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rhs) {
  (void)rhs;
  return *this;
}

bool RPN::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

long RPN::applyOp(long left, long right, char op) {
  if (op == '+')
    return left + right;
  if (op == '-')
    return left - right;
  if (op == '*')
    return left * right;
  if (op == '/') {
    if (right == 0)
      throw std::runtime_error("division by zero");
    return left / right;
  }
  throw std::runtime_error("unknown operator");
}

long RPN::evaluate(const std::string &expr) {
  std::stack<long, std::list<long> > stk;
  std::istringstream iss(expr);
  std::string token;

  while (iss >> token) {
    if (token.size() == 1 && isOperator(token[0])) {
      if (stk.size() < 2)
        throw std::runtime_error("not enough operands");
      long right = stk.top();
      stk.pop();
      long left = stk.top();
      stk.pop();
      stk.push(applyOp(left, right, token[0]));
    } else if (token.size() == 1 && token[0] >= '0' && token[0] <= '9') {
      stk.push(token[0] - '0');
    } else {
      throw std::runtime_error("invalid token");
    }
  }

  if (stk.size() != 1)
    throw std::runtime_error("invalid expression");

  return stk.top();
}
