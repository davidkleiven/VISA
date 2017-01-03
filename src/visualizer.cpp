#include "visualizer.hpp"
#include <iostream>
#include <stdexcept>
//#include <SFML/Color.hpp>
//#define VIS_DEBUG

using namespace std;

visa::Visualizer::Visualizer(){};

visa::Visualizer::~Visualizer()
{
  if ( view != NULL ) delete view;
  if ( window != NULL ) delete window;

  if ( vArray != NULL ) delete vArray;
  if ( tx != NULL ) delete tx;
}

void visa::Visualizer::init( const char *windowName )
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

void visa::Visualizer::init()
{
  init("Default Window");
}

void visa::Visualizer::fillVertexArray( arma::mat &values )
{
  if ( vArray == NULL )
  {
    fillVertexArrayPositions();
  }
  setMaxMinColors( values );

  double rowStep, colStep;
  if (( values.n_rows > height ) && (values.n_cols > width ))
  {
    #ifdef VIS_DEBUG
      clog << "Rows and columns to large\n";
    #endif
    if (( height < defaultHeight ) || (width < defaultWidth ))
    {
      restoreDefaultWindowSize();
      fillVertexArray(values);
      return;
    }

    filterMatrix(values);
    rowStep = static_cast<double>(values.n_rows)/static_cast<double>(height);
    colStep = static_cast<double>(values.n_cols)/static_cast<double>(width);
  }
  else if (( values.n_rows < height ) && ( values.n_cols < width ))
  {
    #ifdef VIS_DEBUG
      clog << "Rows and columns to small\n";
    #endif
    resizeWindow(values.n_cols, values.n_rows);
    rowStep = 1.0;
    colStep = 1.0;
  }
  else if (( values.n_rows == height ) && (values.n_cols == width ))
  {
    #ifdef VIS_DEBUG
      clog << "Rows and columns match\n";
    #endif
    rowStep = 1;
    colStep = 1;
  }
  else if ( values.n_rows < height )
  {
    #ifdef VIS_DEBUG
      clog << "Rows to small\n";
    #endif
    resizeWindow(width, values.n_rows);
    rowStep = 1.0;
    colStep = static_cast<double>(values.n_cols)/static_cast<double>(width);
    filterHorizontal( values );
  }
  else if ( values.n_cols < width )
  {
    #ifdef VIS_DEBUG
      clog << "Columns to small\n";
    #endif
    resizeWindow( values.n_cols, height );
    rowStep = static_cast<double>(values.n_rows)/static_cast<double>(height);
    colStep = 1.0;
    filterVertical( values );
  }
  else
  {
    #ifdef VIS_DEBUG
      clog << "Else clause\n";
    #endif
    resizeWindow(values.n_cols, values.n_rows);
    rowStep = 1;
    colStep = 1;
  }

  for ( unsigned int row=0;row<height;row++ )
  {
    for ( unsigned int col=0;col<width;col++)
    {
      sf::Color color;
      setColor( values(row*rowStep, col*colStep), color);
      (*vArray)[row*width+col].color = color;
    }
  }
  tx->draw(*vArray);
  tx->display();
  sf::Sprite sprite( tx->getTexture());
  // Draw onto screen
  window->draw( sprite );
 //window->draw(*vArray);
}

bool visa::Visualizer::isOpen() const
{
  if ( window != NULL )
  {
    return window->isOpen();
  }
  return false;
}

bool visa::Visualizer::pollEvent( sf::Event &event ) const
{
  if ( window != NULL )
  {
    return window->pollEvent( event );
  }
  return false;
}

double visa::Visualizer::average( const arma::mat &mat )
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

void visa::Visualizer::setColor( double value, sf::Color &color ) const
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

void visa::Visualizer::filterMatrix( arma::mat &mat )
{
  filterHorizontal(mat);
  filterVertical(mat);
}

void visa::Visualizer::filterHorizontal( arma::mat &mat )
{
  filter.setSourceSize( mat.n_cols );
  filter.setTargetSize( width );
  filter.computeFilterCoefficients( filterKernel );

  for ( unsigned int i=0;i<mat.n_rows;i++ )
  {
    arma::subview_row<double> row = mat.row(i);
    filter.filterArray<arma::subview_row<double>, double>( row );
  }
}

void visa::Visualizer::filterVertical( arma::mat &mat )
{
  filter.setSourceSize( mat.n_rows );
  filter.setTargetSize( height );
  filter.computeFilterCoefficients( filterKernel );

  for ( unsigned int i=0;i<mat.n_cols;i++ )
  {
    arma::subview_col<double> col = mat.col(i);
    filter.filterArray<arma::subview_col<double>, double>( col );
  }
}

void visa::Visualizer::fillVertexArrayPositions()
{
  if ( vArray == NULL )
  {
    vArray = new sf::VertexArray(sf::Points, width*height);
  }

  for ( unsigned int row=0;row<height;row++ )
  {
    for ( unsigned int col=0;col<width;col++ )
    {
      (*vArray)[row*width+col].position = window->mapPixelToCoords(sf::Vector2i(col,row));
    }
  }
}

void visa::Visualizer::resizeWindow( unsigned int newWidth, unsigned int newHeight )
{
  width = newWidth;
  height = newHeight;
  //window->setSize(sf::Vector2u(width,height));
  window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
  window->clear();
  if ( vArray != NULL )
  {
    delete vArray;
    vArray = NULL;
  }
  fillVertexArrayPositions();
}

void visa::Visualizer::restoreDefaultWindowSize()
{
  resizeWindow(defaultWidth,defaultHeight);
}

void visa::Visualizer::resizeWidth( unsigned int newWidth )
{
  resizeWindow( newWidth, height );
}

void visa::Visualizer::resizeHeight( unsigned int newHeight )
{
  resizeWindow( width, newHeight );
}

void visa::Visualizer::draw()
{
  if ( vArray != NULL )
  {
    //clog << window->getSize().x << " " << window->getSize().y << endl;
    sf::Sprite sprite( tx->getTexture());
    window->draw(sprite);
  }
}

void visa::Visualizer::setMaxMinColors( arma::mat &intensity )
{
  colorMin = intensity.min();
  colorMax = intensity.max();
}
