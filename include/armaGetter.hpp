#ifndef ARMA_GETTER_H
#define ARMA_GETTER_H
#include <armadillo>

namespace visa
{
  enum class ArmaMatrix_t { ROW, COL };

  /** Default return element in column fixedIndx */
  template <class elemType, ArmaMatrix_t dir>
  class ArmaGetter
  {
  public:
    elemType operator()( arma::Mat<elemType> &mat, unsigned int indx ) const { return mat(indx, fixedIndx); };
    elemType& operator()( arma::Mat<elemType> &mat, unsigned int indx ){ return mat(indx, fixedIndx); };
    unsigned int fixedIndx{0};
  };

  /** Return element in row fixedIndx */
  template<class elemType>
  class ArmaGetter<elemType, ArmaMatrix_t::ROW>
  {
  public:
    elemType operator()( arma::Mat<elemType> &mat, unsigned int indx ) const { return mat(fixedIndx, indx); };
    elemType& operator()( arma::Mat<elemType> &mat, unsigned int indx ){ return mat(fixedIndx, indx); };
    unsigned int fixedIndx{0};
  };
}
#endif
