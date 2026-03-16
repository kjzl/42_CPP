#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>

class Data;

class Serializer {
public:
  static uintptr_t serialize(Data *ptr);
  static Data *deserialization(uintptr_t raw);

private:
  Serializer();
  Serializer(const Serializer &src);
  ~Serializer();

  Serializer &operator=(const Serializer &rhs);
};

#endif
