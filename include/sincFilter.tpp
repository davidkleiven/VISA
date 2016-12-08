template <class arrayType>
void SincFilter::filterArray( arrayType &array ) const
{
  FIFOBuffer buffer( filterCoeff.size() );

  // Initialize buffer
  for ( unsigned int i=0;i<filterCoeff.size()/2;i++)
  {
    buffer.push_back(0.0);
  }
  for ( unsigned int i=0;i<filterCoeff.size()/2-1;i++)
  {
    buffer.push_back(array[i]);
  }

  // Perform filtering
  for ( unsigned int i=0;i<sourceSize-filterCoeff.size()/2-1;i++)
  {
    buffer.push_back(array[i+filterCoeff.size()/2]);
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
    buffer.push_back(0.0);
    double newval = 0.0;
    for ( unsigned int j=0;j<filterCoeff.size();j++ )
    {
      newval += buffer.get(j)*filterCoeff[j];
    }
    array[i] = newval;
  }
}
