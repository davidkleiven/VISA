#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H

class FIFOBuffer
{
public:
  explicit FIFOBuffer( unsigned int size );
  ~FIFOBuffer();
  double get( unsigned int n ) const;
  void push_back( double element );
private:
  unsigned int head{0};
  unsigned int size{0};
  double *values;
};
#endif
