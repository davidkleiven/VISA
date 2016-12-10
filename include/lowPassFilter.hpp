#ifndef SINCFILTER_H
#define SINCFILTER_H
#include <vector>
#include <cassert>
#include "fifoBuffer.hpp"
#include <iostream>

namespace visa
{
class LowPassFilter
{
public:
  LowPassFilter(){};

  /** Set the length of the vector to be filtered */
  void setSourceSize( unsigned int lIn ){ sourceSize=lIn; };

  /** Set the length of the vector that should be returned */
  void setTargetSize( unsigned int lOut ){ targetSize=lOut; };

  /** Computes the filter coefficient corresponding to lengthIn and lengthOut */
  template <class kernelType>
  void computeFilterCoefficients( const kernelType &kernel );

  /** Runs the sinc filter through the array. arrayType must implement operator[] */
  template <class arrayType>
  void filterArray( arrayType &array ) const;
private:
  unsigned int sourceSize{0};
  unsigned int targetSize{0};
  std::vector<double> filterCoeff;
  double sumFilter{0.0};

  /** Nyquist frequency of the output vector */
  double newNyquistFrequency();

  /** Compute the sum of the filter coefficients */
  double sumFilterCoeff() const;

  static double sinc( double x );
};
}; // namespace

#include "lowPassFilter.tpp"
#endif
