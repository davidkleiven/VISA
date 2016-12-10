#include "visualizer.hpp"
#include "windowHandler.hpp"
#include <armadillo>
#include <cmath>
#include <iostream>

using namespace std;

void mexicanHat( double freq, arma::mat &matrix );
int main( int argc, char** argv )
{
  visa::WindowHandler plots;
  try
  {
    plots.addPlot( "Mexican Hat" );
    plots.setActive( "Mexican Hat" );
    plots.getActive().setColorMax(1.0);
    plots.getActive().setColorMin(-1.0);
    arma::mat matrix(700,700);
    mexicanHat( 0.1, matrix );
    plots.getActive().fillVertexArray( matrix );
    plots.show();
    char quit;
    cout << "Press any character to quit...\n";
    cin >> quit;
  }
  catch ( exception &exc )
  {
    cout << exc.what() << endl;
    return 1;
  }
  catch (...)
  {
    cout << "Unexpected exception!\n";
    return 1;
  }

  return 0;
}

// Function implementation
void mexicanHat( double freq, arma::mat &matrix )
{
  // Add 0.01 to avoid problems at i=0 and j=0
  for ( int i=0;i<matrix.n_cols;i++ )
  {
    double x = -static_cast<double>(matrix.n_cols)/2.0 + i+0.01;
    for ( int j=0;j<matrix.n_rows;j++ )
    {
      double y = -static_cast<double>(matrix.n_rows)/2.0+j+0.01;
      double r = sqrt( x*x+y*y );
      matrix(i,j) = sin(freq*r)/(freq*r);
    }
  }
}
