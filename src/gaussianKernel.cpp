#include "gaussianKernel.hpp"
#include <cmath>

visa::GaussianKernel::GaussianKernel(){}

double visa::GaussianKernel::operator()( double x ) const
{
  return exp(-x*x);
}
