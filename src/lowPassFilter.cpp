#include "lowPassFilter.hpp"
#include "fifoBuffer.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;
const double PI = acos(-1.0);

double visa::LowPassFilter::sinc( double x )
{
  if ( abs(x) < 1E-5 )
  {
    return 1.0 - x*x/6.0 + x*x*x*x/120.0;
  }
  return sin(x)/x;
}

double visa::LowPassFilter::newNyquistFrequency()
{
  return PI*targetSize;
}

double visa::LowPassFilter::sumFilterCoeff() const
{
  double sum = 0.0;
  for ( unsigned int i=0;i<filterCoeff.size();i++ )
  {
    sum += filterCoeff[i];
  }
  return sum;
}
