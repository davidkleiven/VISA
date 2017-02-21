#include "visa.hpp"
#include <armadillo>
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main( int argc, char** argv )
{
  // Matrix containing the background
  arma::mat bkg(400,400);
  arma::mat front(400,400);

  // Fill background matrix
  for ( unsigned int i=0;i<bkg.n_cols;i++ )
  {
    for ( unsigned int j=0;j<bkg.n_rows;j++ )
    {
      bkg(j,i) = sin(i/10.0);
      front(j,i) = j*j;
    }
  }

  try
  {
    visa::WindowHandler plots;
    plots.useSeparateDrawing();
    plots.setLayout(2,2);
    plots.addPlot("OnlyFront");
    plots.addPlot("OnlyBkg");
    plots.addPlot("FrontAndBkg");

    // Plot the foreground with the NIPY_SPECTRAL colormap
    visa::Visualizer& pltF = plots.get("OnlyFront");
    visa::Visualizer& pltB = plots.get("OnlyBkg");
    visa::Visualizer& pltFB = plots.get("FrontAndBkg");
    pltF.setCmap( visa::Colormaps::Colormap_t::VIRIDIS );
    pltF.setImg( front );
    plots.draw();

    // Plot background in greyscale
    pltB.setCmap( visa::Colormaps::Colormap_t::GREYSCALE );
    pltB.setImg( bkg );
    plots.draw();

    // Plot both
    pltFB.setCmap( visa::Colormaps::Colormap_t::VIRIDIS );
    pltFB.setImg( front );
    plots.draw();
    pltFB.setCmap( visa::Colormaps::Colormap_t::GREYSCALE );
    pltFB.setOpacity(0.65);
    pltFB.setImg( bkg );
    plots.draw();


    for ( unsigned int i=10;i>0;i--)
    {
      clog << "This will close in " << i << " seconds...\r";
      plots.show();
      this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
  }
  catch( exception &exc )
  {
    cout << exc.what() << endl;
    return 1;
  }
  catch(...)
  {
    cout << "Unrecognized exception!\n";
    return 1;
  }
  return 0;
}
