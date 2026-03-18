#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <deque>
#include <ostream>
#include <stdint.h>
#include <vector>

class PmergeMe {
public:
  uint32_t comparison_count;

  PmergeMe(std::vector<uint32_t> &input);
  PmergeMe(PmergeMe const &src);
  ~PmergeMe();

  PmergeMe &operator=(PmergeMe const &rhs);

  /// Node representing a winner
  /// Points to the loser Node and winner Node of the input nodes.
  class WinnerNode {
  public:
    uint32_t val;
    uint32_t loser_index;
    uint32_t winner_idx;

    WinnerNode();
    WinnerNode(uint32_t v, uint32_t li, uint32_t wi);
    WinnerNode(const WinnerNode &src);
    ~WinnerNode();

    WinnerNode &operator=(const WinnerNode &rhs);

    uint32_t winner_index() const;
  };

  void sortVec();
  void sortDeq();
  const std::vector<WinnerNode> &getSortedVec() const;
  const std::deque<WinnerNode> &getSortedDeq() const;

private:
  class Jacobsthal {

  public:
    Jacobsthal();
    Jacobsthal(Jacobsthal const &src);
    ~Jacobsthal();

    unsigned int next();

    Jacobsthal &operator=(Jacobsthal const &rhs);

  private:
    unsigned int _val;
    unsigned int _next;
  };

  class InsertOrder {

  public:
    InsertOrder(unsigned int indexMax);
    InsertOrder(InsertOrder const &src);
    ~InsertOrder();

    InsertOrder &operator=(InsertOrder const &rhs);

    bool next(unsigned int &outIndex);

  private:
    unsigned int _indexMax;
    unsigned int _smallestNext;
    unsigned int limit;
    Jacobsthal _jac;
    unsigned int _nextIndex;
  };

  class ShiftedInsertOrder {
  public:
    ShiftedInsertOrder(unsigned int indexMax);
    ShiftedInsertOrder(ShiftedInsertOrder const &src);
    ~ShiftedInsertOrder();

    ShiftedInsertOrder &operator=(ShiftedInsertOrder const &rhs);

    bool next(unsigned int &outIndex);
    void shift_indices_at(uint32_t index);
    void reset(uint32_t indexMax);

  private:
    InsertOrder _base;
    std::vector<uint32_t> _shiftedBlockVec;
    std::deque<uint32_t> _shiftedBlockDeq;
    uint32_t _block_size;
    uint32_t _block_i;
    uint32_t _i;
    uint32_t _remaining_next;
    bool _has_next;

    void next_block();
  };

  std::vector<WinnerNode> _vec_in;
  std::vector<WinnerNode> _vec_out;
  std::deque<WinnerNode> _deq_in;
  std::deque<WinnerNode> _deq_out;
  ShiftedInsertOrder _sio;

  uint32_t _len;

  static uint32_t total_winners(uint32_t len);

  template <typename Container>
  uint32_t binaryInsert(Container &out, uint32_t high, const WinnerNode &node,
                        uint32_t *comparisonCount);

  template <typename Container>
  void sort(Container &in, Container &out, uint32_t in_begin, uint32_t in_end,
            uint32_t *comparisonCount);
};

/// display the value of a node
std::ostream &operator<<(std::ostream &o, PmergeMe::WinnerNode const &i);
/// display input vec
std::ostream &operator<<(std::ostream &o, PmergeMe const &i);

template <typename Container>
uint32_t PmergeMe::binaryInsert(Container &out, uint32_t high,
                                const WinnerNode &node,
                                uint32_t *comparisonCount) {
  uint32_t low = 0;
  while (low < high) {
    uint32_t mid = low + (high - low) / 2;
    if (comparisonCount)
      ++(*comparisonCount);
    if (out[mid].val < node.val)
      low = mid + 1;
    else
      high = mid;
  }
  out.insert(out.begin() + static_cast<std::ptrdiff_t>(low), node);
  return low;
}

template <typename Container>
void PmergeMe::sort(Container &in, Container &out, uint32_t in_begin,
                    uint32_t in_end, uint32_t *comparisonCount) {
  uint32_t in_len = in_end - in_begin;
  // base case
  if (in_len <= 1) {
    if (in_len == 1)
      ++(*comparisonCount);
    out.push_back(in[in_begin]);
    return;
  }

  // step 1: Pairwise compare
  uint32_t pair_count = in_len / 2;
  for (uint32_t i = 0; i < pair_count; ++i) {
    uint32_t idx_a = in_begin + i * 2;
    uint32_t val_a = in[idx_a].val;
    uint32_t val_b = in[idx_a + 1].val;
    bool a_is_winner = (val_a >= val_b);
    uint32_t mask =
        0u - static_cast<uint32_t>(a_is_winner); // 0xFFFFFFFF or 0x00000000
    uint32_t winner_val = (val_b & ~mask) | (val_a & mask);
    uint32_t loser_index = idx_a + static_cast<uint32_t>(a_is_winner);
    uint32_t winner_index = idx_a + static_cast<uint32_t>(!a_is_winner);
    in[in_end + i] = WinnerNode(winner_val, loser_index, winner_index);
    ++(*comparisonCount);
  }

  // step 2: recursively sort winners
  sort(in, out, in_end, in_end + pair_count, comparisonCount);

  // step 3: insert losers in order
  uint32_t pairIndex = 0;
  _sio.reset(pair_count - 1);
  do {
    WinnerNode pair_winner = out[pairIndex];
    out[pairIndex] = in[pair_winner.winner_index()];
    uint32_t inserted_at = binaryInsert(
        out, pairIndex, in[pair_winner.loser_index], comparisonCount);
    _sio.shift_indices_at(inserted_at);
  } while (_sio.next(pairIndex));

  // step 4: handle straggler
  if (in_len % 2 == 1) {
    WinnerNode straggler = in[in_end - 1];
    binaryInsert(out, static_cast<uint32_t>(out.size()), straggler,
                 comparisonCount);
  }
}

#endif
