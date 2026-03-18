#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {
public:
  RPN();
  RPN(RPN const &src);
  ~RPN();

  RPN &operator=(RPN const &rhs);

  long evaluate(const std::string &expression) const;

private:
  static bool isOperatorToken(const std::string &token);
  static bool isDigitToken(const std::string &token);
  static long applyOperator(char op, long lhs, long rhs);
};

#endif
