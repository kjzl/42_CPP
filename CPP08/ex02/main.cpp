#include "MutantStack.hpp"
#include <iostream>
#include <list>

static void testSubject() {
  std::cout << "--- Subject test (MutantStack) ---" << std::endl;
  MutantStack<int> mstack;

  mstack.push(5);
  mstack.push(17);

  std::cout << mstack.top() << std::endl;

  mstack.pop();

  std::cout << mstack.size() << std::endl;

  mstack.push(3);
  mstack.push(5);
  mstack.push(737);
  mstack.push(0);

  MutantStack<int>::iterator it = mstack.begin();
  MutantStack<int>::iterator ite = mstack.end();

  ++it;
  --it;
  while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
  }
  std::stack<int> s(mstack);
}

static void testList() {
  std::cout << std::endl;
  std::cout << "--- Subject test (std::list) ---" << std::endl;
  std::list<int> mstack;

  mstack.push_back(5);
  mstack.push_back(17);

  std::cout << mstack.back() << std::endl;

  mstack.pop_back();

  std::cout << mstack.size() << std::endl;

  mstack.push_back(3);
  mstack.push_back(5);
  mstack.push_back(737);
  mstack.push_back(0);

  std::list<int>::iterator it = mstack.begin();
  std::list<int>::iterator ite = mstack.end();

  ++it;
  --it;
  while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
  }
}

static void testCopyAndAssign() {
  std::cout << std::endl;
  std::cout << "--- Copy/Assignment tests ---" << std::endl;

  MutantStack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  MutantStack<int> copy(original);
  std::cout << "Copy top: " << copy.top() << std::endl;
  std::cout << "Copy size: " << copy.size() << std::endl;

  MutantStack<int> assigned;
  assigned = original;
  std::cout << "Assigned top: " << assigned.top() << std::endl;

  // modify original, verify independence
  original.push(99);
  std::cout << "Original size after push: " << original.size() << std::endl;
  std::cout << "Copy size unchanged: " << copy.size() << std::endl;
}

static void testReverseIterator() {
  std::cout << std::endl;
  std::cout << "--- Reverse iterator test ---" << std::endl;

  MutantStack<int> ms;
  ms.push(10);
  ms.push(20);
  ms.push(30);

  MutantStack<int>::reverse_iterator rit = ms.rbegin();
  MutantStack<int>::reverse_iterator rite = ms.rend();
  while (rit != rite) {
    std::cout << *rit << std::endl;
    ++rit;
  }
}

static void testConstIterator() {
  std::cout << std::endl;
  std::cout << "--- Const iterator test ---" << std::endl;

  MutantStack<int> ms;
  ms.push(100);
  ms.push(200);

  const MutantStack<int> &cref = ms;
  MutantStack<int>::const_iterator it = cref.begin();
  MutantStack<int>::const_iterator ite = cref.end();
  while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main() {
  testSubject();
  testList();
  testCopyAndAssign();
  testReverseIterator();
  testConstIterator();
  return 0;
}
