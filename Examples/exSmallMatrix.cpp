#include "windowHandler.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main( int argc, char** argv )
{
  WindowHandler plots;
  try
  {
    // Define plots
    plots.addPlot("200x200");
    plots.addPlot("700x200");
    plots.addPlot("200x700");
    plots.addPlot("700x700");
    plots.setActive("200x200");

    arma::mat mat(200,200);
    arma::mat mat72(700,200);
    arma::mat mat27(200,700);
    arma::mat mat77(700,700);

    mat.randu();
    mat72.randu();
    mat27.randu();
    mat77.randu();
    plots.get("200x200").fillVertexArray(mat);
    plots.get("200x700").fillVertexArray(mat27);
    plots.get("700x200").fillVertexArray(mat72);
    plots.get("700x700").fillVertexArray(mat77);
    for ( unsigned int i=10;i>0;i--)
    {
      clog << "This will close in " << i << " seconds...\r";
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
