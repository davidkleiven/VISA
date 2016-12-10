#include "visualizer.hpp"
#include <iostream>
#include <stdexcept>
//#include <SFML/Color.hpp>

using namespace std;

Visualizer::Visualizer(){};

Visualizer::~Visualizer()
{
  if ( view != NULL ) delete view;
  if ( window != NULL ) delete window;

  if ( vArray != NULL ) delete vArray;
  if ( tx != NULL ) delete tx;
}

void Visualizer::init( const char *windowName )
{
  name = windowName;
  window = new sf::RenderWindow(sf::VideoMode(width, height), windowName);
  window->setKeyRepeatEnabled(false);
  window->clear( sf::Color::Black );
  window->setVerticalSyncEnabled(true);
  fillVertexArrayPositions();

  tx = new sf::RenderTexture();

  //if ( !tx->create(height, width) )
  if ( !tx->create(width, height) )
  {
    throw (runtime_error("Could not create texture!"));
  }

  // Define view
  //view = new sf::View( sf::FloatRect(width/2, height/2, width, height) );
  //window->setView(*view);
}

void Visualizer::init()
{
  init("Default Window");
}

void Visualizer::fillVertexArray( arma::mat &values )
{
  if ( vArray == NULL )
  {
    if ( values.n_rows*values.n_cols > width*height )
    {
      vArrayNrow = height;
      vArrayNcol = width;
    }
    else
    {
      return; // This case is not yet implemented
      vArrayNrow = values.n_rows;
      vArrayNcol = values.n_cols;
    }
    fillVertexArrayPositions();
  }
  filterMatrix(values);
  double rowStep = static_cast<double>(values.n_rows)/static_cast<double>(height);
  double colStep = static_cast<double>(values.n_cols)/static_cast<double>(width);

  for ( unsigned int row=0;row<height;row++ )
  {
    for ( unsigned int col=0;col<width;col++)
    {
      sf::Color color;
      setColor( values(row*rowStep, col*colStep), color);
      (*vArray)[row*width+col].color = color;
    }
  }
  window->draw(*vArray);
}

bool Visualizer::isOpen() const
{
  if ( window != NULL )
  {
    return window->isOpen();
  }
  return false;
}

bool Visualizer::pollEvent( sf::Event &event ) const
{
  if ( window != NULL )
  {
    return window->pollEvent( event );
  }
  return false;
}

double Visualizer::average( const arma::mat &mat )
{
  double avg = 0.0;
  for ( unsigned int i=0;i<mat.n_rows;i++ )
  {
    for ( unsigned int j=0;j<mat.n_cols;j++ )
    {
      avg += mat(i,j);
    }
  }
  return avg/(mat.n_rows*mat.n_cols);
}

void Visualizer::setColor( double value, sf::Color &color ) const
{
  int indx = 255*(value-colorMin)/(colorMax-colorMin);
  indx  = indx > 255 ? 255:indx;
  indx = indx < 0 ? 0:indx;

  switch ( cmap )
  {
    case Colormap_t::VIRIDIS:
      color.r = 255.0*cmaps.viridis[indx][0];
      color.g = 255.0*cmaps.viridis[indx][1];
      color.b = 255.0*cmaps.viridis[indx][2];
      break;
    case Colormap_t::GREYSCALE:
      color.r = indx;
      color.g = indx;
      color.b = indx;
      break;
  }
}

void Visualizer::filterMatrix( arma::mat &mat )
{
  // Filter horizontal
  filter.setSourceSize( mat.n_cols );
  filter.setTargetSize( width );
  filter.computeFilterCoefficients( filterKernel );

  for ( unsigned int i=0;i<mat.n_rows;i++ )
  {
    arma::subview_row<double> row = mat.row(i);
    filter.filterArray( row );
  }

  // Filter vertical
  filter.setSourceSize( mat.n_rows );
  filter.setTargetSize( height );
  filter.computeFilterCoefficients( filterKernel );

  for ( unsigned int i=0;i<mat.n_cols;i++ )
  {
    arma::subview_col<double> col = mat.col(i);
    filter.filterArray( col );
  }
}

void Visualizer::fillVertexArrayPositions()
{
  if ( vArray == NULL )
  {
    vArray = new sf::VertexArray(sf::Points, width*height);
  }

  for ( unsigned int row=0;row<height;row++ )
  {
    for ( unsigned int col=0;col<width;col++ )
    {
      (*vArray)[row*width+col].position = sf::Vector2f(col,row);
    }
  }
}
