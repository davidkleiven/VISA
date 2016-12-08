#ifndef SINCFILTER_H
#define SINCFILTER_H
#include <vector>
#include <cassert>
#include "fifoBuffer.hpp"

class SincFilter
{
public:
  SincFilter(){};

  /** Set the length of the vector to be filtered */
  void setSourceSize( unsigned int lIn ){ sourceSize=lIn; };

  /** Set the length of the vector that should be returned */
  void setTargetSize( unsigned int lOut ){ targetSize=lOut; };

  /** Computes the filter coefficient corresponding to lengthIn and lengthOut */
  void computeFilterCoefficients();

  /** Runs the sinc filter through the array. arrayType must implement operator[] */
  template <class arrayType>
  void filterArray( arrayType &array ) const;
private:
  unsigned int sourceSize{0};
  unsigned int targetSize{0};
  std::vector<double> filterCoeff;

  /** Nyquist frequency of the output vector */
  double newNyquistFrequency();

  static double sinc( double x );
};

#include "sincFilter.tpp"
#endif
