#include "Span.hpp"
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

static void testSubject() {
  std::cout << "--- Subject test ---" << std::endl;
  Span sp = Span(5);
  sp.addNumber(6);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);
  std::cout << sp.shortestSpan() << std::endl;
  std::cout << sp.longestSpan() << std::endl;
}

static void testExceptions() {
  std::cout << std::endl;
  std::cout << "--- Exception tests ---" << std::endl;

  Span empty(0);
  try {
    empty.addNumber(1);
  } catch (const std::exception &e) {
    std::cout << "addNumber on full: " << e.what() << std::endl;
  }

  try {
    empty.shortestSpan();
  } catch (const std::exception &e) {
    std::cout << "shortestSpan on empty: " << e.what() << std::endl;
  }

  Span one(1);
  one.addNumber(42);
  try {
    one.longestSpan();
  } catch (const std::exception &e) {
    std::cout << "longestSpan with 1 element: " << e.what() << std::endl;
  }

  try {
    one.addNumber(99);
  } catch (const std::exception &e) {
    std::cout << "addNumber when full: " << e.what() << std::endl;
  }
}

static void testCopyAndAssign() {
  std::cout << std::endl;
  std::cout << "--- Copy/Assignment tests ---" << std::endl;

  Span original(5);
  original.addNumber(1);
  original.addNumber(10);
  original.addNumber(100);

  Span copy(original);
  copy.addNumber(2000);
  std::cout << "Copy shortest: " << copy.shortestSpan() << std::endl;
  std::cout << "Copy longest: " << copy.longestSpan() << std::endl;

  std::cout << "Original shortest: " << original.shortestSpan() << std::endl;
  std::cout << "Original longest: " << original.longestSpan() << std::endl;


  Span assigned(1);
  assigned = original;
  assigned.addNumber(4000);
  std::cout << "Assigned shortest: " << assigned.shortestSpan() << std::endl;
  std::cout << "Assigned longest: " << assigned.longestSpan() << std::endl;

  std::cout << "Original shortest: " << original.shortestSpan() << std::endl;
  std::cout << "Original longest: " << original.longestSpan() << std::endl;

}

static void testAddRange() {
  std::cout << std::endl;
  std::cout << "--- addRange tests ---" << std::endl;

  std::vector<int> vec;
  vec.push_back(5);
  vec.push_back(3);
  vec.push_back(17);
  vec.push_back(9);
  vec.push_back(11);

  Span sp(5);
  sp.addRange(vec.begin(), vec.end());
  std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
  std::cout << "Longest: " << sp.longestSpan() << std::endl;

  // from a list
  std::list<int> lst;
  lst.push_back(100);
  lst.push_back(200);

  Span sp2(3);
  sp2.addNumber(50);
  sp2.addRange(lst.begin(), lst.end());
  std::cout << "List range shortest: " << sp2.shortestSpan() << std::endl;
  std::cout << "List range longest: " << sp2.longestSpan() << std::endl;

  // overflow
  try {
    sp.addRange(vec.begin(), vec.end());
  } catch (const std::exception &e) {
    std::cout << "addRange overflow: " << e.what() << std::endl;
  }
}

static void testLarge() {
  std::cout << std::endl;
  std::cout << "--- Large test (10000 numbers) ---" << std::endl;

  Span big(10000);
  std::srand(42);
  for (int i = 0; i < 10000; ++i)
    big.addNumber(std::rand());

  std::cout << "Shortest: " << big.shortestSpan() << std::endl;
  std::cout << "Longest: " << big.longestSpan() << std::endl;
}

static void testDuplicates() {
  std::cout << std::endl;
  std::cout << "--- Duplicates test ---" << std::endl;

  Span sp(4);
  sp.addNumber(5);
  sp.addNumber(5);
  sp.addNumber(5);
  sp.addNumber(5);
  std::cout << "Shortest (all same): " << sp.shortestSpan() << std::endl;
  std::cout << "Longest (all same): " << sp.longestSpan() << std::endl;
}

int main() {
  testSubject();
  testExceptions();
  testCopyAndAssign();
  testAddRange();
  testLarge();
  testDuplicates();
  return 0;
}
