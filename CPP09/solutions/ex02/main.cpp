#include "PmergeMe.hpp"

#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static void printErrorAndExit() {
  std::cout << "Error" << std::endl;
  std::exit(1);
}

static bool parsePositiveUint32(const std::string &token, uint32_t &out) {
  if (token.empty())
    return false;

  for (std::string::size_type i = 0; i < token.size(); ++i) {
    if (token[i] < '0' || token[i] > '9')
      return false;
  }

  errno = 0;
  const char *str = token.c_str();
  char *end = 0;
  unsigned long long value = std::strtoull(str, &end, 10);
  if (errno != 0 || end == 0 || *end != '\0')
    return false;
  if (value > 4294967295ULL)
    return false;

  out = static_cast<uint32_t>(value);
  return true;
}

static void printUint32List(const std::vector<uint32_t> &values) {
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (i != 0)
      std::cout << " ";
    std::cout << values[i];
  }
}

static void printUint32ListLimited(const std::vector<uint32_t> &values,
                                   std::size_t limit) {
  const std::size_t n = (values.size() < limit) ? values.size() : limit;
  for (std::size_t i = 0; i < n; ++i) {
    if (i != 0)
      std::cout << " ";
    std::cout << values[i];
  }
  if (values.size() > limit)
    std::cout << " ...";
}

static void
printWinnerNodeList(const std::vector<PmergeMe::WinnerNode> &nodes) {
  for (std::size_t i = 0; i < nodes.size(); ++i) {
    if (i != 0)
      std::cout << " ";
    std::cout << nodes[i].val;
  }
}

static double elapsedMs(std::clock_t start, std::clock_t end) {
  return (static_cast<double>(end - start) * 1000.0) /
         static_cast<double>(CLOCKS_PER_SEC);
}

static std::vector<uint32_t>
extractVals(const std::vector<PmergeMe::WinnerNode> &nodes) {
  std::vector<uint32_t> out;
  out.reserve(nodes.size());
  for (std::size_t i = 0; i < nodes.size(); ++i)
    out.push_back(nodes[i].val);
  return out;
}

static std::vector<uint32_t>
extractVals(const std::deque<PmergeMe::WinnerNode> &nodes) {
  std::vector<uint32_t> out;
  out.reserve(nodes.size());
  for (std::size_t i = 0; i < nodes.size(); ++i)
    out.push_back(nodes[i].val);
  return out;
}

static bool equals(const std::vector<uint32_t> &a,
                   const std::vector<uint32_t> &b) {
  if (a.size() != b.size())
    return false;
  for (std::size_t i = 0; i < a.size(); ++i) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

#include <cmath>
#include <cstddef>

double log2(double x) { return std::log(x) / std::log(2.0); }

// Exact comparison count for Ford–Johnson (merge-insertion) sort
// or just lookup via https://oeis.org/A001768/list
// https://en.wikipedia.org/wiki/Merge-insertion_sort#Analysis
std::size_t expectedFordJohnsonComparisons(std::size_t n) {
  std::size_t comparisons = 0;

  for (std::size_t i = 1; i <= n; ++i) {
    // Compute ceil(log2(3*i/4)) exactly
    double value = (3.0 * i) / 4.0;
    comparisons += static_cast<std::size_t>(std::ceil(::log2(value)));
  }

  return comparisons;
}

int main(int argc, char **argv) {
  // runTesterOrExit();
  // std::cout << "Tester passed." << std::endl;
  (void)runTesterOrExit;

  if (argc < 2)
    printErrorAndExit();

  std::vector<uint32_t> input;
  int i = 1;
  while (i < argc) {
    std::istringstream iss(argv[i]);
    std::string token;
    while (iss >> token) {
      uint32_t value = 0;
      if (!parsePositiveUint32(token, value))
        printErrorAndExit();
      input.push_back(value);
    }
    i++;
  }

  if (input.empty())
    printErrorAndExit();

  std::cout << "Before: ";
  printUint32List(input);
  std::cout << std::endl;

  PmergeMe sorter(input);

  std::clock_t vecStart = std::clock();
  sorter.sortVec();
  std::clock_t vecEnd = std::clock();

  std::cout << "After: ";
  printWinnerNodeList(sorter.getSortedVec());
  std::cout << std::endl;

  std::clock_t deqStart = std::clock();
  sorter.sortDeq();
  std::clock_t deqEnd = std::clock();

  std::cout << std::fixed << std::setprecision(5);
  std::cout << "Time to process a range of " << input.size()
            << " elements with std::vector : " << elapsedMs(vecStart, vecEnd)
            << " ms" << std::endl;
  std::cout << "Time to process a range of " << input.size()
            << " elements with std::deque : " << elapsedMs(deqStart, deqEnd)
            << " ms" << std::endl;
  std::cout << "Comparison count: " << sorter.comparison_count << std::endl;
  std::cout << "Expected comparison count: "
            << expectedFordJohnsonComparisons(input.size()) << std::endl;
  return 0;
}
