#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(const Array &src) : _data(NULL), _size(0) {
  *this = src;
}

template <typename T>
Array<T>::~Array() {
  delete[] _data;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs) {
  if (this != &rhs) {
    delete[] _data;
    _size = rhs._size;
    _data = new T[_size]();
    for (unsigned int i = 0; i < _size; i++)
      _data[i] = rhs._data[i];
  }
  return *this;
}

template <typename T>
T &Array<T>::operator[](unsigned int index) {
  if (index >= _size)
    throw std::out_of_range("index out of bounds");
  return _data[index];
}

template <typename T>
const T &Array<T>::operator[](unsigned int index) const {
  if (index >= _size)
    throw std::out_of_range("index out of bounds");
  return _data[index];
}

template <typename T>
unsigned int Array<T>::size() const {
  return _size;
}

#endif
