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

  static int evaluate(const std::string &expr);

private:
  static bool isOperator(char c);
  static int applyOp(int left, int right, char op);
};

#endif
