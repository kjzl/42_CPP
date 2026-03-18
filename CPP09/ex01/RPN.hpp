#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <stack>
#include <string>

class RPN {
public:
  RPN();
  RPN(const RPN &src);
  ~RPN();

  RPN &operator=(const RPN &rhs);

  static long evaluate(const std::string &expr);

private:
  static bool isOperator(char c);
  static long applyOp(long left, long right, char op);
};

#endif
