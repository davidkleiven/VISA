#include "fifoBuffer.hpp"

using namespace std;
visa::FIFOBuffer::FIFOBuffer( unsigned int size ):size(size)
{
  values = new double[size];
  for ( unsigned int i=0;i<size;i++ )
  {
    values[i] = 0.0;
  }
}
visa::FIFOBuffer::~FIFOBuffer()
{
  delete [] values;
}

double visa::FIFOBuffer::get( unsigned int n ) const
{
  unsigned int indx = (n+head)%size;
  return values[indx];
}

void visa::FIFOBuffer::push_back( double element )
{
  values[head++] = element;
  head = head%size;
}

ostream& visa::operator <<( ostream& out, const visa::FIFOBuffer &buffer )
{
  for ( unsigned int i=0;i<buffer.size;i++ )
  {
    out << buffer.get(i) << " ";
  }
  return out;
}
