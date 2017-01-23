#include "lowPassFilter.hpp"
#include "gaussianKernel.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
double linear( unsigned int n )
{
  return n;
}

double alternating( unsigned int n )
{
  if ( n%2 == 0 ) return 1.0;

  return -1.0;
}

int main()
{
  vector<double> linearRamp;
    arma::mat matrix( 100, 1 );
  for ( unsigned int i=0;i<100;i++ )
  {
    linearRamp.push_back( alternating(i) );
    matrix(i,0) = linearRamp[i];
  }
  vector<double> unfiltered(linearRamp);

  visa::ArmaGetter<double, visa::ArmaMatrix_t::COL> getter;
  getter.fixedIndx = 0;

  visa::GaussianKernel kernel;
  visa::LowPassFilter filter;
  filter.setSourceSize( linearRamp.size() );
  filter.setTargetSize( linearRamp.size()/2 );
  filter.computeFilterCoefficients( kernel );
  filter.filterArray( matrix, getter );

  // Write results to file
  ofstream out;
  string fname ("data/exampleData.csv");
  out.open( fname.c_str() );
  if ( !out.good() )
  {
    cout << "Could not open file!\n";
    return 1;
  }

  out << "# Original signal, filtered signal\n";
  for ( unsigned int i=0;i<linearRamp.size();i++ )
  {
    out << unfiltered[i] << "," << matrix(i,0) << "\n";
  }
  out.close();
  cout << "Data written to " << fname << endl;
  return 0;
}
