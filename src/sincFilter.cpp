#include "sincFilter.hpp"
#include "fifoBuffer.hpp"
#include <cmath>
#include <cassert>

using namespace std;
const double PI = acos(-1.0);

double SincFilter::sinc( double x )
{
  if ( abs(x) < 1E-5 )
  {
    return 1.0 - x*x/6.0 + x*x*x*x/120.0;
  }
  return sin(x)/x;
}

double SincFilter::newNyquistFrequency()
{
  return PI*targetSize;
}

void SincFilter::computeFilterCoefficients()
{
  filterCoeff.clear();
  unsigned int nmax = 2.0*sourceSize/targetSize+1;
  for ( int n=-nmax;n<nmax;n++ )
  {
    double x = PI*targetSize*n/sourceSize;
    filterCoeff.push_back( sinc(x) );
  }
}

void SincFilter::filterArray( double array[] ) const
{
  FIFOBuffer buffer( filterCoeff.size() );

  // Initialize buffer
  for ( unsigned int i=0;i<filterCoeff.size()/2;i++)
  {
    buffer.push_back(0.0);
  }
  for ( unsigned int i=0;i<filterCoeff.size()/2-1;i++)
  {
    buffer.push_back(array[i]);
  }

  // Perform filtering
  for ( unsigned int i=0;i<sourceSize-filterCoeff.size()/2-1;i++)
  {
    buffer.push_back(array[i+filterCoeff.size()/2]);
    double newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    array[i] = newval;
  }

  // Do last part
  for ( unsigned int i=sourceSize-filterCoeff.size()/2; i<sourceSize;i++ )
  {
    buffer.push_back(0.0);
    double newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    array[i] = newval;
  }
}
