#include "fifoBuffer.hpp"
#include <complex>

using namespace std;
template <class T>
visa::FIFOBuffer<T>::FIFOBuffer( unsigned int size ):size(size)
{
  values = new T[size];
  for ( unsigned int i=0;i<size;i++ )
  {
    values[i] = 0.0;
  }
}

template <class T>
visa::FIFOBuffer<T>::~FIFOBuffer()
{
  delete [] values;
}

template <class T>
T visa::FIFOBuffer<T>::get( unsigned int n ) const
{
  unsigned int indx = (n+head)%size;
  return values[indx];
}

template <class T>
void visa::FIFOBuffer<T>::push_back( T element )
{
  values[head++] = element;
  head = head%size;
}

template <class T>
ostream& visa::operator <<( ostream& out, const visa::FIFOBuffer<T> &buffer )
{
  for ( unsigned int i=0;i<buffer.size;i++ )
  {
    out << buffer.get(i) << " ";
  }
  return out;
}

// Explicit instantiation
template class visa::FIFOBuffer<double>;
template class visa::FIFOBuffer<complex<double> >;
