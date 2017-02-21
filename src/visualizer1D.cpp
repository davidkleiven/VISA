#include "visualizer1D.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
void visa::Visualizer1D::setLimits( double minVal, double maxVal )
{
  min = minVal;
  max = maxVal;
}

unsigned int visa::Visualizer1D::getY( double val ) const
{
  int indx = ( (val-min)/(max-min) )*height;
  indx = indx > height ? height-1:indx;
  indx = indx < 0 ? 0:indx;
  return height-indx;
}

void visa::Visualizer1D::fillVertexArray( arma::vec &vec )
{
  if ( vArray == NULL )
  {
    vArray = new sf::VertexArray( sf::LinesStrip, width );
  }

  unsigned int color = rand()%256;
  sf::Color col;
  col.r = rand()%256;
  col.g = rand()%256;
  col.b = rand()%256;

  if ( vec.n_elem > width )
  {
    double step = static_cast<double>(vec.n_elem)/static_cast<double>(width);
    for ( unsigned int i=0;i<width;i++ )
    {
      unsigned int y1 = getY( vec( static_cast<unsigned int>(i*step)) );
      (*vArray)[i].position = sf::Vector2f(i,y1);
      (*vArray)[i].color = col;
    }
  }
  else
  {
    double pixStep = static_cast<double>(width)/vec.n_elem;
    for ( unsigned int i=0;i<width;i++ )
    {
      unsigned int y1 = getY( vec(i) );
      (*vArray)[i].position = sf::Vector2f(i*pixStep,y1);
      (*vArray)[i].color = col;
    }
  }

  // Draw onto screen
  //window->draw( *vArray );
}

void visa::Visualizer1D::init( const char* windowname )
{
  visa::Visualizer::init( windowname );

  // Delete the vertex array as this should be handled by this class
  if ( vArray != NULL )
  {
    delete vArray;
    vArray = NULL;
  }
}
