#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array {
public:
  Array();
  Array(unsigned int n);
  Array(const Array &src);
  ~Array();

  Array &operator=(const Array &rhs);

  T &operator[](unsigned int index);
  const T &operator[](unsigned int index) const;

  unsigned int size() const;

private:
  T *_data;
  unsigned int _size;
};

#include "Array.tpp"

#endif
