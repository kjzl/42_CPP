#include "Span.hpp"
#include <algorithm>
#include <climits>

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span &src) {
  *this = src;
}

Span::~Span() {}

Span &Span::operator=(const Span &rhs) {
  if (this != &rhs) {
    _maxSize = rhs._maxSize;
    _data = rhs._data;
  }
  return *this;
}

void Span::addNumber(int number) {
  if (_data.size() >= _maxSize)
    throw std::runtime_error("Span is full");
  _data.push_back(number);
}

unsigned int Span::shortestSpan() const {
  if (_data.size() < 2)
    throw std::runtime_error("not enough elements to find a span");

  std::vector<int> sorted(_data);
  std::sort(sorted.begin(), sorted.end());

  unsigned int minSpan = UINT_MAX;
  for (std::vector<int>::size_type i = 1; i < sorted.size(); ++i) {
    unsigned int diff = static_cast<unsigned int>(sorted[i])
      - static_cast<unsigned int>(sorted[i - 1]);
    if (diff < minSpan)
      minSpan = diff;
  }
  return minSpan;
}

unsigned int Span::longestSpan() const {
  if (_data.size() < 2)
    throw std::runtime_error("not enough elements to find a span");

  int min = *std::min_element(_data.begin(), _data.end());
  int max = *std::max_element(_data.begin(), _data.end());
  return static_cast<unsigned int>(max) - static_cast<unsigned int>(min);
}
