template <class elemType, visa::ArmaMatrix_t dir>
void visa::LowPassFilter::filterArray( arma::Mat<elemType> &array, visa::ArmaGetter<elemType,dir> &getter ) const
{
  assert ( filterCoeff.size() > 0 );
  visa::FIFOBuffer<elemType> buffer( filterCoeff.size() );


  // Initialize buffer
  for ( unsigned int i=0;i<filterCoeff.size()/2;i++)
  {
    buffer.push_back( getter(array,0) );
  }

  for ( unsigned int i=0;i<filterCoeff.size()/2-1;i++)
  {
    buffer.push_back( getter(array,i) );
  }

  // Perform filtering
  for ( unsigned int i=0;i<sourceSize-filterCoeff.size()/2;i++)
  {
    buffer.push_back( getter( array, i+filterCoeff.size()/2-1 ) );
    elemType newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    getter( array, i ) = newval;
  }

  // Do last part
  for ( unsigned int i=sourceSize-filterCoeff.size()/2; i<sourceSize;i++ )
  {
    buffer.push_back( getter(array, sourceSize-1) );
    elemType newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    getter( array, i ) = newval;
  }
}

template <class kernelType>
void visa::LowPassFilter::computeFilterCoefficients( const kernelType &kernel )
{
  filterCoeff.clear();
  int nmax = 2.0*sourceSize/targetSize+1;
  for ( int n=-nmax;n<=nmax;n++ )
  {
    double x = targetSize*n/sourceSize;
    filterCoeff.push_back( kernel(x) );
  }
  double sum = sumFilterCoeff();
  for ( unsigned int i=0;i<filterCoeff.size();i++ )
  {
    filterCoeff[i] /= sum;
  }
}
