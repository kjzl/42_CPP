#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class Data {
public:
  Data();
  Data(const std::string &name, int value);
  Data(const Data &src);
  ~Data();

  Data &operator=(const Data &rhs);

  std::string getName() const;
  int getValue() const;

private:
  std::string _name;
  int _value;
};

#endif
