#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H
#include <iostream>

namespace visa{
class FIFOBuffer
{
public:
  explicit FIFOBuffer( unsigned int size );
  ~FIFOBuffer();
  double get( unsigned int n ) const;
  void push_back( double element );
  friend std::ostream& operator <<(std::ostream& out, const FIFOBuffer &buffer );
private:
  unsigned int head{0};
  unsigned int size{0};
  double *values;
};
std::ostream& operator <<(std::ostream& out, const FIFOBuffer &buffer );
}; // namespace
#endif
