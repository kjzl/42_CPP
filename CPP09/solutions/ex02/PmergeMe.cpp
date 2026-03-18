#include "PmergeMe.hpp"

#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <ostream>

// Jacobsthal

PmergeMe::Jacobsthal::Jacobsthal() : _val(3), _next(5) {}

PmergeMe::Jacobsthal::Jacobsthal(const Jacobsthal &src)
    : _val(src._val), _next(src._next) {}

PmergeMe::Jacobsthal::~Jacobsthal() {}

PmergeMe::Jacobsthal &PmergeMe::Jacobsthal::operator=(Jacobsthal const &rhs) {
  if (this != &rhs) {
    this->_next = rhs._next;
    this->_val = rhs._val;
  }
  return *this;
}

unsigned int PmergeMe::Jacobsthal::next() {
  unsigned int last = _val;
  _val = _next;
  _next = 2 * last + _val;
  return last;
}

// InsertOrder

PmergeMe::InsertOrder::InsertOrder(unsigned int indexMax)
    : _indexMax(indexMax), _smallestNext(1), limit(0), _nextIndex(UINT_MAX) {}

PmergeMe::InsertOrder::InsertOrder(const InsertOrder &src) { *this = src; }

PmergeMe::InsertOrder::~InsertOrder() {}

PmergeMe::InsertOrder &
PmergeMe::InsertOrder::operator=(InsertOrder const &rhs) {
  if (this != &rhs) {
    _indexMax = rhs._indexMax;
    _smallestNext = rhs._smallestNext;
    _jac = rhs._jac;
    limit = rhs.limit;
    _nextIndex = rhs._nextIndex;
  }
  return *this;
}

bool PmergeMe::InsertOrder::next(unsigned int &outIndex) {
  if (limit < _smallestNext) {
    if (_smallestNext > _indexMax)
      return false;
    limit = std::min(_jac.next() - 1, _indexMax);
    _nextIndex = limit;
  }

  outIndex = _nextIndex;
  if (_nextIndex == _smallestNext) {
    _smallestNext = limit + 1;
  } else {
    --_nextIndex;
  }
  return true;
}

// ShiftedInsertOrder

PmergeMe::ShiftedInsertOrder::ShiftedInsertOrder(uint32_t inputLen)
    : _base(0), _i(1) {
  _shiftedBlockVec.resize(inputLen / 2);
  _shiftedBlockDeq.resize(inputLen / 2);
}

PmergeMe::ShiftedInsertOrder::ShiftedInsertOrder(const ShiftedInsertOrder &src)
    : _base(src._base), _shiftedBlockVec(src._shiftedBlockVec),
      _shiftedBlockDeq(src._shiftedBlockDeq), _block_size(src._block_size),
      _block_i(src._block_i), _i(src._i), _remaining_next(src._remaining_next),
      _has_next(src._has_next) {}

PmergeMe::ShiftedInsertOrder::~ShiftedInsertOrder() {}

PmergeMe::ShiftedInsertOrder &
PmergeMe::ShiftedInsertOrder::operator=(ShiftedInsertOrder const &rhs) {
  if (this != &rhs) {
    this->_base = rhs._base;
    this->_shiftedBlockVec = rhs._shiftedBlockVec;
    this->_shiftedBlockDeq = rhs._shiftedBlockDeq;
    this->_block_size = rhs._block_size;
    this->_block_i = rhs._block_i;
    this->_i = rhs._i;
    this->_remaining_next = rhs._remaining_next;
    this->_has_next = rhs._has_next;
  }
  return *this;
}

void PmergeMe::ShiftedInsertOrder::reset(uint32_t indexMax) {
  _base = InsertOrder(indexMax);
  _block_size = 0;
  _block_i = 0;
  _i = 1;
  _has_next = _base.next(_remaining_next);
}

bool PmergeMe::ShiftedInsertOrder::next(unsigned int &outIndex) {
  if (_block_i >= _block_size) {
    if (!_has_next)
      return false;
    next_block();
  }
  outIndex = _shiftedBlockVec[_block_i++];
  ++_i;
  return true;
}

void PmergeMe::ShiftedInsertOrder::shift_indices_at(uint32_t index) {
  uint32_t i = _block_i;
  while (i < _block_size) {
    if (_shiftedBlockVec[i] >= index)
      _shiftedBlockVec[i]++;
    i++;
  }
}

void PmergeMe::ShiftedInsertOrder::next_block() {
  // if this is called, _has_next is true and _remaining_next is our first index
  _block_i = 0;
  _shiftedBlockVec[0] = _remaining_next + _i;
  _block_size = 1;
  while (_base.next(_remaining_next)) {
    _remaining_next += _i;
    if (_remaining_next != _shiftedBlockVec[_block_size - 1] - 1) {
      _remaining_next -= _i;
      return; // _has_next remains true
    }
    _shiftedBlockVec[_block_size] = _remaining_next;
    _block_size++;
  }
  _has_next = false;
}

// WINNERNODE

PmergeMe::WinnerNode::WinnerNode() : val(0), loser_index(0), winner_idx(0) {}

PmergeMe::WinnerNode::WinnerNode(uint32_t v, uint32_t li, uint32_t wi)
    : val(v), loser_index(li), winner_idx(wi) {}

PmergeMe::WinnerNode::WinnerNode(const WinnerNode &src) { *this = src; }

PmergeMe::WinnerNode::~WinnerNode() {}

PmergeMe::WinnerNode &PmergeMe::WinnerNode::operator=(const WinnerNode &rhs) {
  if (this != &rhs) {
    val = rhs.val;
    loser_index = rhs.loser_index;
    winner_idx = rhs.winner_idx;
  }
  return *this;
}

uint32_t PmergeMe::WinnerNode::winner_index() const { return winner_idx; }

std::ostream &operator<<(std::ostream &o, PmergeMe::WinnerNode const &i) {
  o << i.val;
  return o;
}

// PmergeMe

std::ostream &operator<<(std::ostream &o, PmergeMe const &i) {
  for (uint32_t idx = 0; idx < i.getSortedVec().size(); ++idx) {
    if (idx != 0)
      o << " ";
    o << i.getSortedVec()[idx].val;
  }
  return o;
}

// winners len shrinks by ~1/2 each recursion: floor(n/2) + floor(n/4) + ... < n
static uint32_t total_winners(uint32_t len) {
  uint32_t total = 0;
  uint32_t n = len / 2;
  while (n > 0) {
    total += n;
    n /= 2;
  }
  return total;
}

PmergeMe::PmergeMe(std::vector<uint32_t> &input)
    : comparison_count(0), _sio(input.size()) {
  _len = input.size();
  uint32_t needed_capacity = _len + total_winners(_len);
  _vec_in.reserve(needed_capacity);
  _vec_out.reserve(_len);
  for (std::vector<uint32_t>::iterator it = input.begin(); it != input.end();
       ++it) {
    WinnerNode node(*it, 0, 0);
    _vec_in.push_back(node);
    _deq_in.push_back(node);
  }
  // We store intermediate "winner" nodes in-place at fixed indices
  // (in_end + i). Ensure the containers are sized upfront.
  _vec_in.resize(needed_capacity);
  // deque doesnt have .reserve
  _deq_in.resize(needed_capacity);
}

PmergeMe::PmergeMe(PmergeMe const &src) : _sio(src._len) { *this = src; }

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
  if (this != &rhs) {
    this->comparison_count = rhs.comparison_count;
    this->_vec_in = rhs._vec_in;
    this->_vec_out = rhs._vec_out;
    this->_deq_in = rhs._deq_in;
    this->_deq_out = rhs._deq_out;
    this->_len = rhs._len;
  }
  return *this;
}

void PmergeMe::sortVec() {
  _vec_out.clear();
  sort(_vec_in, _vec_out, 0, _len, &comparison_count);
}

void PmergeMe::sortDeq() {
  _deq_out.clear();
  sort(_deq_in, _deq_out, 0, _len, 0);
}

const std::vector<PmergeMe::WinnerNode> &PmergeMe::getSortedVec() const {
  return _vec_out;
}

const std::deque<PmergeMe::WinnerNode> &PmergeMe::getSortedDeq() const {
  return _deq_out;
}
