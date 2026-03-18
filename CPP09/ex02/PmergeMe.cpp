#include "PmergeMe.hpp"

#include <algorithm>
#include <cstddef>

#ifdef DEBUG
#include <cmath>
#include <iostream>
#endif

// Jacobsthal

PmergeMe::Jacobsthal::Jacobsthal() : _val(3), _next(5) {}

PmergeMe::Jacobsthal::Jacobsthal(const Jacobsthal &src) { *this = src; }

PmergeMe::Jacobsthal::~Jacobsthal() {}

PmergeMe::Jacobsthal &
PmergeMe::Jacobsthal::operator=(const Jacobsthal &rhs) {
  if (this != &rhs) {
    _val = rhs._val;
    _next = rhs._next;
  }
  return *this;
}

// Returns the current Jacobsthal value and advances the sequence.
// Sequence: 3, 5, 11, 21, 43, 85, ... (each value = prev + 2 * prev_prev)
unsigned int PmergeMe::Jacobsthal::next() {
  unsigned int last = _val;
  _val = _next;
  _next = 2 * last + _val;
  return last;
}

// InsertOrder

PmergeMe::InsertOrder::InsertOrder()
    : _indexMax(0), _smallestNext(1), _limit(0), _nextIndex(0) {}

PmergeMe::InsertOrder::InsertOrder(unsigned int indexMax)
    : _indexMax(indexMax), _smallestNext(1), _limit(0), _nextIndex(0) {}

PmergeMe::InsertOrder::InsertOrder(const InsertOrder &src) { *this = src; }

PmergeMe::InsertOrder::~InsertOrder() {}

PmergeMe::InsertOrder &
PmergeMe::InsertOrder::operator=(const InsertOrder &rhs) {
  if (this != &rhs) {
    _indexMax = rhs._indexMax;
    _smallestNext = rhs._smallestNext;
    _limit = rhs._limit;
    _jac = rhs._jac;
    _nextIndex = rhs._nextIndex;
  }
  return *this;
}

// Yields the next pair index in Jacobsthal batch order.
// When the current batch is exhausted (_limit < _smallestNext), a new batch
// is started: the Jacobsthal generator gives t_k, and the batch covers
// indices [_smallestNext .. min(t_k - 1, _indexMax)] in descending order.
bool PmergeMe::InsertOrder::next(unsigned int &outIndex) {
  if (_limit < _smallestNext) {
    if (_smallestNext > _indexMax)
      return false;
    _limit = std::min(_jac.next() - 1, _indexMax);
    _nextIndex = _limit;
  }

  outIndex = _nextIndex;
  if (_nextIndex == _smallestNext)
    _smallestNext = _limit + 1;
  else
    --_nextIndex;
  return true;
}

// ShiftedInsertOrder

PmergeMe::ShiftedInsertOrder::ShiftedInsertOrder()
    : _blockSize(0), _blockIdx(0), _insertCount(1),
      _pendingNext(0), _hasNext(false) {}

PmergeMe::ShiftedInsertOrder::ShiftedInsertOrder(unsigned int capacity)
    : _blockSize(0), _blockIdx(0), _insertCount(1),
      _pendingNext(0), _hasNext(false) {
  _blocks.resize(capacity / 2);
}

PmergeMe::ShiftedInsertOrder::ShiftedInsertOrder(
    const ShiftedInsertOrder &src) { *this = src; }

PmergeMe::ShiftedInsertOrder::~ShiftedInsertOrder() {}

PmergeMe::ShiftedInsertOrder &
PmergeMe::ShiftedInsertOrder::operator=(const ShiftedInsertOrder &rhs) {
  if (this != &rhs) {
    _base = rhs._base;
    _blocks = rhs._blocks;
    _blockSize = rhs._blockSize;
    _blockIdx = rhs._blockIdx;
    _insertCount = rhs._insertCount;
    _pendingNext = rhs._pendingNext;
    _hasNext = rhs._hasNext;
  }
  return *this;
}

// Re-initialize for a new recursion level with the given maximum pair index.
// _insertCount starts at 1 because pair 0 (the first loser, which is known
// to be less than its winner) is always processed before this iterator yields
// any indices — so one insertion has already occurred.
void PmergeMe::ShiftedInsertOrder::reset(unsigned int indexMax) {
  _base = InsertOrder(indexMax);
  _blockSize = 0;
  _blockIdx = 0;
  _insertCount = 1;
  _hasNext = _base.next(_pendingNext);
}

// Returns the next output-chain position to process.
// If the current block is exhausted, fetches the next Jacobsthal batch.
bool PmergeMe::ShiftedInsertOrder::next(unsigned int &outIndex) {
  if (_blockIdx >= _blockSize) {
    if (!_hasNext)
      return false;
    nextBlock();
  }
  outIndex = _blocks[_blockIdx];
  ++_blockIdx;
  ++_insertCount;
  return true;
}

// After inserting a loser at position 'index' in the output chain, all
// pending positions in the current batch that are >= index must be
// incremented by 1, because the insertion shifted them right.
void PmergeMe::ShiftedInsertOrder::shiftIndicesAt(unsigned int index) {
  for (unsigned int i = _blockIdx; i < _blockSize; ++i) {
    if (_blocks[i] >= index)
      ++_blocks[i];
  }
}

// Fetches the next Jacobsthal batch and converts abstract pair indices to
// concrete output-chain positions.
//
// Each abstract pair index p from InsertOrder maps to output position
// p + _insertCount (accounting for all prior loser insertions). Consecutive
// batch members must be exactly 1 apart in the output chain (descending);
// if a gap is detected, the remaining index is saved for the next batch.
void PmergeMe::ShiftedInsertOrder::nextBlock() {
  _blockIdx = 0;
  _blocks[0] = _pendingNext + _insertCount;
  _blockSize = 1;

  while (_base.next(_pendingNext)) {
    unsigned int shifted = _pendingNext + _insertCount;
    if (shifted != _blocks[_blockSize - 1] - 1) {
      return;
    }
    _blocks[_blockSize] = shifted;
    ++_blockSize;
  }
  _hasNext = false;
}

// WinnerNode

PmergeMe::WinnerNode::WinnerNode()
    : _val(0), _loserIndex(0), _winnerIndex(0) {}

PmergeMe::WinnerNode::WinnerNode(unsigned int val, unsigned int loserIndex,
                                 unsigned int winnerIndex)
    : _val(val), _loserIndex(loserIndex), _winnerIndex(winnerIndex) {}

PmergeMe::WinnerNode::WinnerNode(const WinnerNode &src) { *this = src; }

PmergeMe::WinnerNode::~WinnerNode() {}

PmergeMe::WinnerNode &
PmergeMe::WinnerNode::operator=(const WinnerNode &rhs) {
  if (this != &rhs) {
    _val = rhs._val;
    _loserIndex = rhs._loserIndex;
    _winnerIndex = rhs._winnerIndex;
  }
  return *this;
}

unsigned int PmergeMe::WinnerNode::getVal() const { return _val; }

unsigned int PmergeMe::WinnerNode::getLoserIndex() const {
  return _loserIndex;
}

unsigned int PmergeMe::WinnerNode::getWinnerIndex() const {
  return _winnerIndex;
}

// PmergeMe (non-instantiable)

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) { (void)src; }

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
  (void)rhs;
  return *this;
}

// Total winner-node slots needed across all recursion levels.
// Each level pairs floor(n/2) elements, producing floor(n/2) winners.
// The sum floor(n/2) + floor(n/4) + ... converges to less than n.
unsigned int PmergeMe::totalWinners(unsigned int len) {
  unsigned int total = 0;
  unsigned int n = len / 2;
  while (n > 0) {
    total += n;
    n /= 2;
  }
  return total;
}

// std::vector workspace

void PmergeMe::buildWorkspace(const std::vector<unsigned int> &input,
                              std::vector<WinnerNode> &workspace) {
  unsigned int len = static_cast<unsigned int>(input.size());
  unsigned int capacity = len + totalWinners(len);
  workspace.resize(capacity);
  for (unsigned int i = 0; i < len; ++i)
    workspace[i] = WinnerNode(input[i], 0, 0);
}

// std::deque workspace

void PmergeMe::buildWorkspace(const std::deque<unsigned int> &input,
                              std::deque<WinnerNode> &workspace) {
  unsigned int len = static_cast<unsigned int>(input.size());
  unsigned int capacity = len + totalWinners(len);
  workspace.resize(capacity);
  for (unsigned int i = 0; i < len; ++i)
    workspace[i] = WinnerNode(input[i], 0, 0);
}

// Binary search for the correct position of 'node' in out[0..high),
// insert there, and return the insertion index.

unsigned int PmergeMe::binaryInsert(std::vector<WinnerNode> &out,
                                    unsigned int high,
                                    const WinnerNode &node,
                                    unsigned int &compCount) {
  unsigned int low = 0;
  while (low < high) {
    unsigned int mid = low + (high - low) / 2;
    ++compCount;
    if (out[mid].getVal() < node.getVal())
      low = mid + 1;
    else
      high = mid;
  }
  out.insert(out.begin() + static_cast<std::ptrdiff_t>(low), node);
  return low;
}

unsigned int PmergeMe::binaryInsert(std::deque<WinnerNode> &out,
                                    unsigned int high,
                                    const WinnerNode &node,
                                    unsigned int &compCount) {
  unsigned int low = 0;
  while (low < high) {
    unsigned int mid = low + (high - low) / 2;
    ++compCount;
    if (out[mid].getVal() < node.getVal())
      low = mid + 1;
    else
      high = mid;
  }
  out.insert(out.begin() + static_cast<std::ptrdiff_t>(low), node);
  return low;
}

// Ford-Johnson merge-insertion sort — recursive implementation.
//
// The workspace 'in' holds original elements at [0, originalLen) and has
// reserved space beyond that for winner nodes created during pairing.
// The 'out' container accumulates the sorted result for this recursion level.
//
// Algorithm overview:
//   Phase 1 — Pairwise compare: form floor(n/2) pairs from in[begin..end),
//     compare each, and write winner nodes into in[end..end+pairCount).
//     Each winner node stores the value plus indices of both the winner and
//     loser elements from the level below.
//
//   Phase 2 — Recursive sort: recursively sort the winner nodes. The output
//     is a sorted sequence of winner nodes, each still carrying references
//     to the level below.
//
//   Phase 3 — Jacobsthal insertion: build the sorted output by unwrapping
//     winner nodes and inserting their associated losers. Pair 0's loser
//     is inserted first (no comparison needed — it's known to be less than
//     its winner). Remaining losers are inserted in Jacobsthal batch order,
//     binary-searching only the prefix before their winner's current
//     position. ShiftedInsertOrder tracks how positions shift as elements
//     are inserted.
//
//   The straggler (unpaired element when n is odd) is folded into the
//     Jacobsthal order rather than inserted separately. This ensures its
//     search range is bounded by the Jacobsthal batch structure, keeping
//     comparisons within the Ford-Johnson bound. When the yielded position
//     equals out.size(), we know it's the straggler (no associated winner).

void PmergeMe::sortRecursive(std::vector<WinnerNode> &in,
                             std::vector<WinnerNode> &out,
                             unsigned int begin, unsigned int end,
                             unsigned int &compCount,
                             ShiftedInsertOrder &sio) {
  unsigned int len = end - begin;
  if (len == 0)
    return;
  if (len == 1) {
    out.push_back(in[begin]);
    return;
  }

  // phase 1: branchless pairwise compare
  // mask is all-ones (0xFFFFFFFF) when a wins, all-zeros when b wins.
  // This selects winner/loser values and indices without branching.
  unsigned int pairCount = len / 2;
  for (unsigned int i = 0; i < pairCount; ++i) {
    unsigned int idxA = begin + i * 2;
    unsigned int valA = in[idxA].getVal();
    unsigned int valB = in[idxA + 1].getVal();
    ++compCount;

    unsigned int aWins = static_cast<unsigned int>(valA >= valB);
    unsigned int mask = 0u - aWins;
    unsigned int winnerVal = (valA & mask) | (valB & ~mask);
    unsigned int winnerIdx = idxA + (aWins ^ 1u);
    unsigned int loserIdx = idxA + aWins;
    // if/else equivalent:
    // if (valA >= valB) {
    //   winnerVal = valA;
    //   winnerIdx = idxA;
    //   loserIdx = idxA + 1;
    // } else {
    //   winnerVal = valB;
    //   winnerIdx = idxA + 1;
    //   loserIdx = idxA;
    // }
    in[end + i] = WinnerNode(winnerVal, loserIdx, winnerIdx);
  }

  // phase 2: recursively sort winners
  sortRecursive(in, out, end, end + pairCount, compCount, sio);

  // phase 3: insert losers (and straggler) in Jacobsthal order
  // Include straggler in the Jacobsthal order so its search range is
  // optimally bounded. When pairIndex == out.size(), it's the straggler.
  bool hasStraggler = (len % 2 == 1);
  unsigned int sioMax = pairCount - 1;
  if (hasStraggler)
    sioMax = pairCount;

  unsigned int pairIndex = 0;
  sio.reset(sioMax);
  do {
    unsigned int insertedAt;
    if (pairIndex >= static_cast<unsigned int>(out.size())) {
      insertedAt = binaryInsert(
          out, static_cast<unsigned int>(out.size()),
          in[end - 1], compCount);
    } else {
      WinnerNode pairWinner = out[pairIndex];
      out[pairIndex] = in[pairWinner.getWinnerIndex()];
      insertedAt = binaryInsert(
          out, pairIndex, in[pairWinner.getLoserIndex()], compCount);
    }
    sio.shiftIndicesAt(insertedAt);
  } while (sio.next(pairIndex));
}

// std::deque overload — same algorithm as the vector version above.

void PmergeMe::sortRecursive(std::deque<WinnerNode> &in,
                             std::deque<WinnerNode> &out,
                             unsigned int begin, unsigned int end,
                             unsigned int &compCount,
                             ShiftedInsertOrder &sio) {
  unsigned int len = end - begin;
  if (len == 0)
    return;
  if (len == 1) {
    out.push_back(in[begin]);
    return;
  }

  unsigned int pairCount = len / 2;
  for (unsigned int i = 0; i < pairCount; ++i) {
    unsigned int idxA = begin + i * 2;
    unsigned int valA = in[idxA].getVal();
    unsigned int valB = in[idxA + 1].getVal();
    ++compCount;

    unsigned int aWins = static_cast<unsigned int>(valA >= valB);
    unsigned int mask = 0u - aWins;
    unsigned int winnerVal = (valA & mask) | (valB & ~mask);
    unsigned int winnerIdx = idxA + (aWins ^ 1u);
    unsigned int loserIdx = idxA + aWins;
    in[end + i] = WinnerNode(winnerVal, loserIdx, winnerIdx);
  }

  sortRecursive(in, out, end, end + pairCount, compCount, sio);

  bool hasStraggler = (len % 2 == 1);
  unsigned int sioMax = pairCount - 1;
  if (hasStraggler)
    sioMax = pairCount;
  unsigned int pairIndex = 0;
  sio.reset(sioMax);
  do {
    unsigned int insertedAt;
    if (pairIndex >= static_cast<unsigned int>(out.size())) {
      insertedAt = binaryInsert(
          out, static_cast<unsigned int>(out.size()),
          in[end - 1], compCount);
    } else {
      WinnerNode pairWinner = out[pairIndex];
      out[pairIndex] = in[pairWinner.getWinnerIndex()];
      insertedAt = binaryInsert(
          out, pairIndex, in[pairWinner.getLoserIndex()], compCount);
    }
    sio.shiftIndicesAt(insertedAt);
  } while (sio.next(pairIndex));
}

// Public sort entry points

unsigned int PmergeMe::sort(const std::vector<unsigned int> &in,
                            std::vector<unsigned int> &out) {
  unsigned int len = static_cast<unsigned int>(in.size());
  if (len == 0) {
    out.clear();
    return 0;
  }

  std::vector<WinnerNode> workspace;
  buildWorkspace(in, workspace);

  std::vector<WinnerNode> sorted;
  sorted.reserve(len);

  ShiftedInsertOrder sio(len);
  unsigned int compCount = 0;
  sortRecursive(workspace, sorted, 0, len, compCount, sio);

  out.clear();
  out.reserve(len);
  for (unsigned int i = 0; i < len; ++i)
    out.push_back(sorted[i].getVal());
  return compCount;
}

unsigned int PmergeMe::sort(const std::deque<unsigned int> &in,
                            std::deque<unsigned int> &out) {
  unsigned int len = static_cast<unsigned int>(in.size());
  if (len == 0) {
    out.clear();
    return 0;
  }

  std::deque<WinnerNode> workspace;
  buildWorkspace(in, workspace);

  std::deque<WinnerNode> sorted;

  ShiftedInsertOrder sio(len);
  unsigned int compCount = 0;
  sortRecursive(workspace, sorted, 0, len, compCount, sio);

  out.clear();
  for (unsigned int i = 0; i < len; ++i)
    out.push_back(sorted[i].getVal());
  return compCount;
}

#ifdef DEBUG

// Upper bound on comparisons for an optimal-comparison sort of n elements.
// Formula: sum_{i=1}^{n} ceil(log2(3*i / 4))
// Reference: OEIS A001768, Knuth TAOCP Vol.3 "Merge Insertion"
unsigned int PmergeMe::expectedFordJohnsonComparisons(unsigned int n) {
  unsigned int comparisons = 0;
  for (unsigned int i = 1; i <= n; ++i) {
    double value = (3.0 * static_cast<double>(i)) / 4.0;
    double lg = std::log(value) / std::log(2.0);
    int c = static_cast<int>(std::ceil(lg));
    if (c > 0)
      comparisons += static_cast<unsigned int>(c);
  }
  return comparisons;
}

void PmergeMe::printInsertOrder(unsigned int indexMax) {
  std::cout << "InsertOrder(indexMax=" << indexMax << "): [0]";
  InsertOrder io(indexMax);
  unsigned int idx;
  while (io.next(idx))
    std::cout << " " << idx;
  std::cout << std::endl;
}

#endif
