#include "visa.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <armadillo>
#include <cstdlib>
#include <ctime>

using namespace std;

int main( int argc, char** argv )
{
  srand(time(0));
  arma::vec gaussian(700);
  for ( int i=0;i<gaussian.n_elem;i++ )
  {
    double x = static_cast<double>(i)-static_cast<double>(gaussian.n_elem)/2.0;
    gaussian(i) = exp(-x*x*0.0001);
  }
  visa::WindowHandler plots;
  try
  {
    plots.addLinePlot("Gaussian");
    plots.get("Gaussian").setLimits(0.0,1.2);
    plots.get("Gaussian").fillVertexArray(gaussian);
    for ( unsigned int i=0;i<10;i++ )
    {
      clog << "Closes in " << 10-i << " sec...\r";
      plots.show();
      this_thread::sleep_for(chrono::seconds(1));
    }
  }
  catch ( exception &exc )
  {
    cout << exc.what() << endl;
    return 1;
  }
  catch (...)
  {
    cout << "Unrecognized exception!\n";
    return 1;
  }
  return 0;
}
