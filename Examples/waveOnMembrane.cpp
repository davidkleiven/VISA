#include "visa.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);
double Lx = 500.0;
double Ly = 800.0;
double freq = 0.05;

double eigenMode( double x, double y, unsigned int nx, unsigned int ny )
{
  return sin( nx*PI*x/Lx)*sin( ny*PI*y/Ly);
}

int main( int argc, char** argv )
{
  visa::WindowHandler plots;
  plots.addPlot("Eigenmode");
  plots.get("Eigenmode").setCmap( visa::Colormaps::Colormap_t::NIPY_SPECTRAL );
  plots.get("Eigenmode").setColorLim( -1.0, 1.0 );
  try
  {
    arma::mat solution(Ly,Lx);
    for ( unsigned int ix=0;ix<Lx;ix++ )
    {
      for ( unsigned int iy=0;iy<Ly;iy++ )
      {
        solution(iy,ix) = eigenMode( ix, iy, 1, 1 );
      }
    }

    for ( unsigned int t=0;t<100;t++ )
    {
      arma::mat timesignal = solution*sin( freq*t );
      plots.get("Eigenmode").fillVertexArray( timesignal );
      plots.show();
      plots.get("Eigenmode").clear();
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
