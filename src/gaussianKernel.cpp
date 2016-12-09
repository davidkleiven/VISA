#include "gaussianKernel.hpp"
#include <cmath>

GaussianKernel::GaussianKernel(){}

double GaussianKernel::operator()( double x ) const
{
  return exp(-x*x);
}
