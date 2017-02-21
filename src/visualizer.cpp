#include "visualizer.hpp"
#include <iostream>
#include <stdexcept>
#include <omp.h>
//#include <SFML/Color.hpp>
//#define VIS_DEBUG

using namespace std;

visa::Visualizer::Visualizer(){};

visa::Visualizer::~Visualizer()
{
  if ( vArray != NULL ) delete vArray;
  if ( pixels != NULL ) delete [] pixels;
  if ( img != NULL ) delete img;
}

void visa::Visualizer::init( const char *windowName )
{
  name = windowName;
  img = new sf::Image();
}

void visa::Visualizer::init()
{
  init("Default Window");
}

void visa::Visualizer::setImg( arma::mat &values )
{
  if ( !colorLimitsSetByUser )
  {
    setMaxMinColors( values );
  }

  assert( img != NULL );

  if ( nPix != values.n_rows*values.n_cols )
  {
    if ( pixels != NULL ) delete pixels;
    pixels = new sf::Uint8[4*values.n_rows*values.n_cols];
    nPix = values.n_rows*values.n_cols;
  }

  for ( unsigned int row=0;row<values.n_rows;row++ )
  {
    for ( unsigned int col=0;col<values.n_cols;col++)
    {
      sf::Color color;
      setColor( values(row, col), color);
      pixels[4*(values.n_cols*row+col)] = color.r;
      pixels[4*(values.n_cols*row+col)+1] = color.g;
      pixels[4*(values.n_cols*row+col)+2] = color.b;
      pixels[4*(values.n_cols*row+col)+3] = alpha;
    }
  }
  img->create( values.n_rows, values.n_cols, pixels );
}

void visa::Visualizer::fillVertexArray( arma::mat &values )
{
  setImg( values );
}

void visa::Visualizer::setColor( double value, sf::Color &color ) const
{
  int indx = 255*(value-colorMin)/(colorMax-colorMin);
  indx  = indx > 255 ? 255:indx;
  indx = indx < 0 ? 0:indx;

  cmaps.setColor( indx, color );
}

void visa::Visualizer::setMaxMinColors( arma::mat &intensity )
{
  colorMin = intensity.min();
  colorMax = intensity.max();
}

void visa::Visualizer::setColorLim( double min, double max )
{
  colorLimitsSetByUser = true;
  colorMin = min;
  colorMax = max;
}

void visa::Visualizer::setOpacity( double newAlpha )
{
  if ( newAlpha < 0.0 )
  {
    newAlpha = 0.0;
  }
  else if ( newAlpha > 1.0 )
  {
    newAlpha = 1.0;
  }
  alpha = 255.0*newAlpha;
}
