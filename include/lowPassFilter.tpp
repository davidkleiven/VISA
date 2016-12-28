template <class arrayType, class elemType>
void visa::LowPassFilter::filterArray( arrayType &array ) const
{
  assert ( filterCoeff.size() > 0 );
  visa::FIFOBuffer<elemType> buffer( filterCoeff.size() );


  // Initialize buffer
  for ( unsigned int i=0;i<filterCoeff.size()/2;i++)
  {
    buffer.push_back(array[0]);
  }

  for ( unsigned int i=0;i<filterCoeff.size()/2-1;i++)
  {
    buffer.push_back(array[i]);
  }

  // Perform filtering
  for ( unsigned int i=0;i<sourceSize-filterCoeff.size()/2;i++)
  {
    buffer.push_back(array[i+filterCoeff.size()/2-1]);
    double newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    array[i] = newval;
  }

  // Do last part
  for ( unsigned int i=sourceSize-filterCoeff.size()/2; i<sourceSize;i++ )
  {
    buffer.push_back(array[sourceSize-1]);
    double newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    array[i] = newval;
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
