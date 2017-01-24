#ifndef ARMA_GETTER_H
#define ARMA_GETTER_H
#include <armadillo>
/**
This is some templated classes for getting an element from an armadillo matrix.
They are written to both be able to efficiently filter both rows and
columns of an Armadillo matrix using the lowPassFilter class.
*/

namespace visa
{
  enum class ArmaMatrix_t { ROW, COL, VECTOR };

  /** Default return element in column fixedIndx */
  template <class elemType, ArmaMatrix_t dir>
  class ArmaGetter
  {
  public:
    const elemType& operator()( arma::Mat<elemType> &mat, unsigned int indx ) const { return mat(indx, fixedIndx); };
    elemType& operator()( arma::Mat<elemType> &mat, unsigned int indx ){ return mat(indx, fixedIndx); };
    unsigned int fixedIndx{0};
  };

  /** Return element in row fixedIndx */
  template<class elemType>
  class ArmaGetter<elemType, ArmaMatrix_t::ROW>
  {
  public:
    const elemType& operator()( arma::Mat<elemType> &mat, unsigned int indx ) const { return mat(fixedIndx, indx); };
    elemType& operator()( arma::Mat<elemType> &mat, unsigned int indx ){ return mat(fixedIndx, indx); };
    unsigned int fixedIndx{0};
  };

  /** Use this to run a low pass filter on a armadillo column vector */
  template<class elemType>
  class ArmaGetter<elemType, ArmaMatrix_t::VECTOR>
  {
  public:
    const elemType& operator()( arma::Mat<elemType> &vec, unsigned int indx ) const { return vec(indx); };
    elemType& operator()( arma::Mat<elemType> &vec, unsigned int indx ){ return vec(indx); };
    unsigned int fixedIndx{0}; // Unused, but needs to be declared for compatibility with the low pass filter
  };
}
#endif
