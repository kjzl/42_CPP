#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
  Data data("test", 42);

  std::cout << "Original pointer:     " << &data << std::endl;
  std::cout << "Data name:            " << data.getName() << std::endl;
  std::cout << "Data value:           " << data.getValue() << std::endl;

  uintptr_t raw = Serializer::serialize(&data);
  std::cout << "Serialized (raw):     " << raw << std::endl;

  Data *result = Serializer::deserialization(raw);
  std::cout << "Deserialized pointer: " << result << std::endl;

  if (result == &data)
    std::cout << "Pointers match!" << std::endl;
  else
    std::cout << "Pointers do NOT match!" << std::endl;

  std::cout << "Result name:          " << result->getName() << std::endl;
  std::cout << "Result value:         " << result->getValue() << std::endl;

  return 0;
}
