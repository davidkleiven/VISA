#include "fifoBuffer.hpp"

using namespace std;
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
  values[head++] = element;
  head = head%size;
}

ostream& operator <<( ostream& out, const FIFOBuffer &buffer )
{
  for ( unsigned int i=0;i<buffer.size;i++ )
  {
    out << buffer.get(i) << " ";
  }
  return out;
}
