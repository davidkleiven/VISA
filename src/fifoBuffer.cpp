#include "fifoBuffer.hpp"

FIFOBuffer::FIFOBuffer( unsigned int size ):size(size)
{
  values = new double[size];
  for ( unsigned int i=0;i<size;i++ )
  {
    values[i] = 0.0;
  }
}
FIFOBuffer::~FIFOBuffer()
{
  delete [] values;
}

double FIFOBuffer::get( unsigned int n ) const
{
  unsigned int indx = (n+head)%size;
  return values[indx];
}

void FIFOBuffer::push_back( double element )
{
  values[head] = element;
  head++;
  head = head%size;
}
