#ifndef GAUSSIAN_KERNEL_H
#define GAUSSIAN_KERNEL_H

namespace visa
{
class GaussianKernel
{
public:
  GaussianKernel();
  double operator()( double x ) const;
};
};
#endif
