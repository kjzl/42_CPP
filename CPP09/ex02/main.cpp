#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static bool parseUint(const std::string &token, unsigned int &out) {
  if (token.empty())
    return false;
  for (std::string::size_type i = 0; i < token.size(); ++i) {
    if (token[i] < '0' || token[i] > '9')
      return false;
  }

  errno = 0;
  char *end = NULL;
  unsigned long value = std::strtoul(token.c_str(), &end, 10);
  if (errno != 0 || end == NULL || *end != '\0')
    return false;
  if (value == 0 || value > UINT_MAX)
    return false;

  out = static_cast<unsigned int>(value);
  return true;
}

static bool parse(int argc, char **argv,
                  std::vector<unsigned int> &vec,
                  std::deque<unsigned int> &deq) {
  for (int i = 1; i < argc; ++i) {
    std::istringstream iss(argv[i]);
    std::string token;
    while (iss >> token) {
      unsigned int value = 0;
      if (!parseUint(token, value))
        return false;
      vec.push_back(value);
      deq.push_back(value);
    }
  }
  return !vec.empty();
}

static double getTimeUs() {
  return static_cast<double>(std::clock()) / CLOCKS_PER_SEC * 1000000.0;
}

static void printSequence(const std::vector<unsigned int> &v) {
  for (std::vector<unsigned int>::size_type i = 0; i < v.size(); ++i) {
    if (i != 0)
      std::cout << " ";
    std::cout << v[i];
  }
}

#ifdef DEBUG

#include <algorithm>

static bool isSorted(const std::vector<unsigned int> &v) {
  for (std::vector<unsigned int>::size_type i = 1; i < v.size(); ++i) {
    if (v[i] < v[i - 1])
      return false;
  }
  return true;
}

static bool sameElements(std::vector<unsigned int> a,
                         std::vector<unsigned int> b) {
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

static std::vector<unsigned int> deqToVec(const std::deque<unsigned int> &d) {
  return std::vector<unsigned int>(d.begin(), d.end());
}

static bool hasDuplicates(const std::vector<unsigned int> &v) {
  std::vector<unsigned int> sorted(v);
  std::sort(sorted.begin(), sorted.end());
  for (std::vector<unsigned int>::size_type i = 1; i < sorted.size(); ++i) {
    if (sorted[i] == sorted[i - 1])
      return true;
  }
  return false;
}

static bool runTest(const std::vector<unsigned int> &input,
                    const std::string &name) {
  std::vector<unsigned int> vecOut;
  std::deque<unsigned int> deqIn(input.begin(), input.end());
  std::deque<unsigned int> deqOut;

  double vecStart = getTimeUs();
  unsigned int vecComps = PmergeMe::sort(input, vecOut);
  double vecTime = getTimeUs() - vecStart;

  double deqStart = getTimeUs();
  unsigned int deqComps = PmergeMe::sort(deqIn, deqOut);
  double deqTime = getTimeUs() - deqStart;

  std::vector<unsigned int> deqOutVec = deqToVec(deqOut);
  unsigned int expected = 0;
  if (!input.empty())
    expected = PmergeMe::expectedFordJohnsonComparisons(
        static_cast<unsigned int>(input.size()));

  bool pass = true;
  std::string failures;

  if (!isSorted(vecOut)) {
    pass = false;
    failures += " vec-not-sorted";
  }
  if (!isSorted(deqOutVec)) {
    pass = false;
    failures += " deq-not-sorted";
  }
  if (!sameElements(input, vecOut)) {
    pass = false;
    failures += " vec-wrong-elements";
  }
  if (!sameElements(input, deqOutVec)) {
    pass = false;
    failures += " deq-wrong-elements";
  }
  if (vecOut != deqOutVec) {
    pass = false;
    failures += " vec-deq-mismatch";
  }

  // Ford-Johnson comparison bound only holds for distinct elements
  bool checkComps = !hasDuplicates(input);
  if (checkComps && vecComps > expected) {
    pass = false;
    failures += " vec-too-many-comps";
  }
  if (checkComps && deqComps > expected) {
    pass = false;
    failures += " deq-too-many-comps";
  }

  if (pass) {
    std::cout << "[PASS] " << name
              << " (n=" << input.size()
              << ", comps=" << vecComps
              << "/" << expected
              << ", vec=" << static_cast<long>(vecTime) << "us"
              << ", deq=" << static_cast<long>(deqTime) << "us)" << std::endl;
  } else {
    std::cout << "[FAIL] " << name
              << " (n=" << input.size()
              << ", vec_comps=" << vecComps
              << ", deq_comps=" << deqComps
              << ", expected_max=" << expected
              << ", vec=" << static_cast<long>(vecTime) << "us"
              << ", deq=" << static_cast<long>(deqTime) << "us"
              << "):" << failures << std::endl;
  }
  return pass;
}

// Generates a vector of 'size' unique values via Fisher-Yates shuffle
// of [1..size], ensuring no duplicates so the comparison bound applies.
static std::vector<unsigned int> randomUniqueVec(unsigned int size) {
  std::vector<unsigned int> v;
  v.reserve(size);
  for (unsigned int i = 1; i <= size; ++i)
    v.push_back(i);
  for (unsigned int i = size; i > 1; --i) {
    unsigned int j = static_cast<unsigned int>(std::rand()) % i;
    unsigned int tmp = v[i - 1];
    v[i - 1] = v[j];
    v[j] = tmp;
  }
  return v;
}

static int runTestSuite() {
  unsigned int passed = 0;
  unsigned int failed = 0;

  std::cout << "=== PmergeMe Debug Tests ===" << std::endl;
  std::cout << std::endl;

  // InsertOrder examples (pair 0 is always first, shown as [0])
  PmergeMe::printInsertOrder(2);
  PmergeMe::printInsertOrder(3);
  PmergeMe::printInsertOrder(15);
  std::cout << std::endl;

  // hardcoded tests
  {
    unsigned int a[] = {1};
    if (runTest(std::vector<unsigned int>(a, a + 1), "single element"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {2, 1};
    if (runTest(std::vector<unsigned int>(a, a + 2), "two elements"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {1, 2};
    if (runTest(std::vector<unsigned int>(a, a + 2), "two sorted"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {3, 1, 2};
    if (runTest(std::vector<unsigned int>(a, a + 3), "three elements"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {3, 5, 9, 7, 4};
    if (runTest(std::vector<unsigned int>(a, a + 5), "subject example"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {8, 7, 6, 5, 4, 3, 2, 1};
    if (runTest(std::vector<unsigned int>(a, a + 8), "reverse sorted 8"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    if (runTest(std::vector<unsigned int>(a, a + 8), "already sorted 8"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {3, 1, 3, 2, 1};
    if (runTest(std::vector<unsigned int>(a, a + 5), "duplicates"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {5, 5, 5, 5, 5};
    if (runTest(std::vector<unsigned int>(a, a + 5), "all same"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {42};
    if (runTest(std::vector<unsigned int>(a, a + 1), "single large"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    if (runTest(std::vector<unsigned int>(a, a + 10), "reverse sorted 10"))
      ++passed;
    else
      ++failed;
  }
  {
    unsigned int a[] = {1, 3, 2, 5, 4, 7, 6};
    if (runTest(std::vector<unsigned int>(a, a + 7), "interleaved 7"))
      ++passed;
    else
      ++failed;
  }

  std::cout << std::endl;

  // random tests with fixed seed
  std::srand(42);
  unsigned int sizes[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    15, 20, 31, 50, 63, 100, 127, 255,
    500, 1000, 3000
  };
  unsigned int numSizes = sizeof(sizes) / sizeof(sizes[0]);

  for (unsigned int s = 0; s < numSizes; ++s) {
    std::ostringstream name;
    name << "random n=" << sizes[s];
    if (runTest(randomUniqueVec(sizes[s]), name.str()))
      ++passed;
    else
      ++failed;
  }

  // second random run with different seed
  std::srand(12345);
  for (unsigned int s = 0; s < numSizes; ++s) {
    std::ostringstream name;
    name << "random2 n=" << sizes[s];
    if (runTest(randomUniqueVec(sizes[s]), name.str()))
      ++passed;
    else
      ++failed;
  }

  std::cout << std::endl;
  std::cout << "Tests passed: " << passed << "/"
            << (passed + failed) << std::endl;

  if (failed > 0) {
    std::cout << "SOME TESTS FAILED" << std::endl;
    return 1;
  }
  std::cout << "ALL TESTS PASSED" << std::endl;
  return 0;
}

static int runWithArgs(int argc, char **argv) {
  std::vector<unsigned int> vec;
  std::deque<unsigned int> deq;
  if (!parse(argc, argv, vec, deq)) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::cout << "Before: ";
  printSequence(vec);
  std::cout << std::endl;

  std::vector<unsigned int> vecOut;
  double vecStart = getTimeUs();
  unsigned int vecComps = PmergeMe::sort(vec, vecOut);
  double vecTime = getTimeUs() - vecStart;

  std::deque<unsigned int> deqOut;
  double deqStart = getTimeUs();
  unsigned int deqComps = PmergeMe::sort(deq, deqOut);
  double deqTime = getTimeUs() - deqStart;

  std::cout << "After: ";
  printSequence(vecOut);
  std::cout << std::endl;

  std::cout << "Time to process a range of " << vec.size()
            << " elements with std::vector : "
            << static_cast<long>(vecTime) << " us" << std::endl;
  std::cout << "Time to process a range of " << vec.size()
            << " elements with std::deque  : "
            << static_cast<long>(deqTime) << " us" << std::endl;

  unsigned int expected = PmergeMe::expectedFordJohnsonComparisons(
      static_cast<unsigned int>(vec.size()));
  std::cout << "Comparisons: vec=" << vecComps
            << ", deq=" << deqComps
            << ", max=" << expected << std::endl;
  if (vecComps > expected || deqComps > expected) {
    std::cerr << "WARNING: comparison count exceeds Ford-Johnson bound!"
              << std::endl;
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2)
    return runTestSuite();
  return runWithArgs(argc, argv);
}

#else

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::vector<unsigned int> vec;
  std::deque<unsigned int> deq;
  if (!parse(argc, argv, vec, deq)) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::cout << "Before: ";
  printSequence(vec);
  std::cout << std::endl;

  std::vector<unsigned int> vecOut;
  double vecStart = getTimeUs();
  PmergeMe::sort(vec, vecOut);
  double vecTime = getTimeUs() - vecStart;

  std::deque<unsigned int> deqOut;
  double deqStart = getTimeUs();
  PmergeMe::sort(deq, deqOut);
  double deqTime = getTimeUs() - deqStart;

  std::cout << "After: ";
  printSequence(vecOut);
  std::cout << std::endl;

  std::cout << "Time to process a range of " << vec.size()
            << " elements with std::vector : "
            << static_cast<long>(vecTime) << " us" << std::endl;
  std::cout << "Time to process a range of " << vec.size()
            << " elements with std::deque  : "
            << static_cast<long>(deqTime) << " us" << std::endl;

  return 0;
}

#endif
