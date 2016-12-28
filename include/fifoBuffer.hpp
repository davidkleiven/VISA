#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H
#include <iostream>

namespace visa{

template <class T>
class FIFOBuffer
{
public:
  explicit FIFOBuffer( unsigned int size );
  ~FIFOBuffer();
  T get( unsigned int n ) const;
  void push_back( T element );
  template <class U>
  friend std::ostream& operator <<(std::ostream& out, const FIFOBuffer<U> &buffer );
private:
  unsigned int head{0};
  unsigned int size{0};
  T *values;
};

template <class T>
std::ostream& operator <<(std::ostream& out, const FIFOBuffer<T> &buffer );
}; // namespace
#endif
