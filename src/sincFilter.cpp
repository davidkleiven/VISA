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
