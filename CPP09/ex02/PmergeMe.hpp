#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

class PmergeMe {
public:
  static unsigned int sort(const std::vector<unsigned int> &in,
                           std::vector<unsigned int> &out);
  static unsigned int sort(const std::deque<unsigned int> &in,
                           std::deque<unsigned int> &out);

#ifdef DEBUG
  static unsigned int expectedFordJohnsonComparisons(unsigned int n);
  static void printInsertOrder(unsigned int indexMax);
#endif

private:
  PmergeMe();
  PmergeMe(const PmergeMe &src);
  ~PmergeMe();
  PmergeMe &operator=(const PmergeMe &rhs);

  // Represents a winner from a pairwise comparison. Stores the winning value
  // plus indices back into the workspace for both the winner and loser
  // elements, preserving the pairing across recursion levels.
  class WinnerNode {
  public:
    WinnerNode();
    WinnerNode(unsigned int val, unsigned int loserIndex,
               unsigned int winnerIndex);
    WinnerNode(const WinnerNode &src);
    ~WinnerNode();

    WinnerNode &operator=(const WinnerNode &rhs);

    unsigned int getVal() const;
    unsigned int getLoserIndex() const;
    unsigned int getWinnerIndex() const;

  private:
    unsigned int _val;
    unsigned int _loserIndex;
    unsigned int _winnerIndex;
  };

  // Generates the Jacobsthal sequence: 3, 5, 11, 21, 43, ...
  // Recurrence: t(k) = t(k-1) + 2*t(k-2). These values define the batch
  // boundaries for the Ford-Johnson insertion phase. Each batch is sized so
  // that binary insertion into the available prefix costs at most k comparisons
  // (the prefix has at most 2^k - 1 elements).
  class Jacobsthal {
  public:
    Jacobsthal();
    Jacobsthal(const Jacobsthal &src);
    ~Jacobsthal();

    Jacobsthal &operator=(const Jacobsthal &rhs);

    unsigned int next();

  private:
    unsigned int _val;
    unsigned int _next;
  };

  // Yields loser-pair indices in Ford-Johnson insertion order.
  // Within each Jacobsthal batch [prev+1 .. t_k], indices are emitted
  // in descending order (t_k, t_k-1, ..., prev+1). Descending order
  // ensures each binary insertion searches a prefix no larger than 2^k - 1,
  // keeping the comparison count optimal.
  class InsertOrder {
  public:
    InsertOrder();
    InsertOrder(unsigned int indexMax);
    InsertOrder(const InsertOrder &src);
    ~InsertOrder();

    InsertOrder &operator=(const InsertOrder &rhs);

    bool next(unsigned int &outIndex);

  private:
    unsigned int _indexMax;
    unsigned int _smallestNext;
    unsigned int _limit;
    Jacobsthal _jac;
    unsigned int _nextIndex;
  };

  // Adapts InsertOrder to track actual positions in the growing output chain.
  // When a loser is inserted, all elements after the insertion point shift
  // right by one. This class converts abstract pair indices from InsertOrder
  // into concrete output-chain positions by:
  //   1. Adding _insertCount (total prior insertions) as a base offset.
  //   2. Calling shiftIndicesAt() after each insertion to bump any pending
  //      indices in the current batch that are at or past the insertion point.
  class ShiftedInsertOrder {
  public:
    ShiftedInsertOrder();
    ShiftedInsertOrder(unsigned int capacity);
    ShiftedInsertOrder(const ShiftedInsertOrder &src);
    ~ShiftedInsertOrder();

    ShiftedInsertOrder &operator=(const ShiftedInsertOrder &rhs);

    bool next(unsigned int &outIndex);
    void shiftIndicesAt(unsigned int index);
    void reset(unsigned int indexMax);

  private:
    InsertOrder _base;
    std::vector<unsigned int> _blocks;
    unsigned int _blockSize;
    unsigned int _blockIdx;
    unsigned int _insertCount;
    unsigned int _pendingNext;
    bool _hasNext;

    void nextBlock();
  };

  static unsigned int totalWinners(unsigned int len);

  static void buildWorkspace(const std::vector<unsigned int> &input,
                             std::vector<WinnerNode> &workspace);
  static void buildWorkspace(const std::deque<unsigned int> &input,
                             std::deque<WinnerNode> &workspace);

  static void sortRecursive(std::vector<WinnerNode> &in,
                            std::vector<WinnerNode> &out,
                            unsigned int begin, unsigned int end,
                            unsigned int &compCount,
                            ShiftedInsertOrder &sio);
  static void sortRecursive(std::deque<WinnerNode> &in,
                            std::deque<WinnerNode> &out,
                            unsigned int begin, unsigned int end,
                            unsigned int &compCount,
                            ShiftedInsertOrder &sio);

  static unsigned int binaryInsert(std::vector<WinnerNode> &out,
                                   unsigned int high,
                                   const WinnerNode &node,
                                   unsigned int &compCount);
  static unsigned int binaryInsert(std::deque<WinnerNode> &out,
                                   unsigned int high,
                                   const WinnerNode &node,
                                   unsigned int &compCount);
};

#endif
