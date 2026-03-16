#include "Data.hpp"

Data::Data() : _name(""), _value(0) {}

Data::Data(const std::string &name, int value) : _name(name), _value(value) {}

Data::Data(const Data &src) { *this = src; }

Data::~Data() {}

Data &Data::operator=(const Data &rhs) {
  if (this != &rhs) {
    _name = rhs._name;
    _value = rhs._value;
  }
  return *this;
}

std::string Data::getName() const { return _name; }

int Data::getValue() const { return _value; }
