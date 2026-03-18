#ifndef SPAN_HPP
#define SPAN_HPP

#include <stdexcept>
#include <vector>

class Span {
public:
  Span();
  Span(unsigned int n);
  Span(const Span &src);
  ~Span();

  Span &operator=(const Span &rhs);

  void addNumber(int number);

  template <typename InputIterator>
  void addRange(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      if (_data.size() >= _maxSize)
        throw std::runtime_error("adding range would exceed Span capacity");
      _data.push_back(*first);
    }
  }

  unsigned int shortestSpan() const;
  unsigned int longestSpan() const;

private:
  unsigned int _maxSize;
  std::vector<int> _data;
};

#endif
