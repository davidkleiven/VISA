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
  if ( view != NULL ) delete view;
  if ( window != NULL ) delete window;

  if ( vArray != NULL ) delete vArray;
  if ( tx != NULL ) delete tx;
  if ( pixels != NULL ) delete [] pixels;
}

void visa::Visualizer::init( const char *windowName )
{
  name = windowName;
  window = new sf::RenderWindow(sf::VideoMode(width, height), windowName);
  window->setKeyRepeatEnabled(false);
  window->clear( sf::Color::Black );
  window->setVerticalSyncEnabled(true);

  pixels = new sf::Uint8[width*height*4];

  tx = new sf::Texture();

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
  if ( !colorLimitsSetByUser )
  {
    setMaxMinColors( values );
  }

  double rowStep, colStep;
  if (( values.n_rows > height ) && (values.n_cols > width ))
  {
    #ifdef VIS_DEBUG
      clog << "Rows and columns to large\n";
    #endif
    if (( height != defaultHeight ) || (width != defaultWidth ))
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
    //resizeWindow(values.n_cols, values.n_rows);
    width = values.n_cols;
    height = values.n_rows;
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
  else if ( values.n_rows <= height )
  {
    #ifdef VIS_DEBUG
      clog << "Rows to small\n";
    #endif
    //resizeWindow(width, values.n_rows);
    height = values.n_rows;
    rowStep = 1.0;
    colStep = static_cast<double>(values.n_cols)/static_cast<double>(width);
    filterHorizontal( values );
  }
  else if ( values.n_cols <= width )
  {
    #ifdef VIS_DEBUG
      clog << "Columns to small\n";
    #endif
    //resizeWindow( values.n_cols, height );
    width = values.n_cols;
    rowStep = static_cast<double>(values.n_rows)/static_cast<double>(height);
    colStep = 1.0;
    filterVertical( values );
  }
  else
  {
    #ifdef VIS_DEBUG
      clog << "Else clause\n";
    #endif
    //sresizeWindow(values.n_cols, values.n_rows);
    width = values.n_cols;
    height = values.n_cols;
    rowStep = 1;
    colStep = 1;
  }

  for ( unsigned int row=0;row<height;row++ )
  {
    for ( unsigned int col=0;col<width;col++)
    {
      sf::Color color;
      setColor( values(row*rowStep, col*colStep), color);
      pixels[4*(width*row+col)] = color.r;
      pixels[4*(width*row+col)+1] = color.g;
      pixels[4*(width*row+col)+2] = color.b;
      pixels[4*(width*row+col)+3] = 255;
    }
  }

  img.create( width, height, pixels );
  tx->update( img );
  sf::Sprite sprite( *tx );

  // Draw onto screen
  window->draw( sprite );

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

void visa::Visualizer::setColor( double value, sf::Color &color ) const
{
  int indx = 255*(value-colorMin)/(colorMax-colorMin);
  indx  = indx > 255 ? 255:indx;
  indx = indx < 0 ? 0:indx;

  cmaps.setColor( indx, color );
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

  unsigned int maxThreads = omp_get_num_threads();
  vector< visa::ArmaGetter<double,visa::ArmaMatrix_t::ROW> > getters;
  for ( unsigned int i=0;i<maxThreads;i++ )
  {
    getters.push_back( visa::ArmaGetter<double,visa::ArmaMatrix_t::ROW>() );
  }

  #pragma omp parallel
  {
    unsigned int id = omp_get_thread_num();
    #pragma omp for
    for ( unsigned int i=0;i<mat.n_rows;i++ )
    {
      getters[id].fixedIndx = i;
      filter.filterArray( mat, getters[id] );
    }
  }
}

void visa::Visualizer::filterVertical( arma::mat &mat )
{
  filter.setSourceSize( mat.n_rows );
  filter.setTargetSize( height );
  filter.computeFilterCoefficients( filterKernel );
  unsigned int maxThreads = omp_get_num_threads();

  // Initialize one getter for each thread
  vector< visa::ArmaGetter<double, visa::ArmaMatrix_t::COL > > getters;
  for ( unsigned int i=0;i<maxThreads;i++ )
  {
    getters.push_back( visa::ArmaGetter<double, visa::ArmaMatrix_t::COL>() );
  }

  // Run the filtering in parallel
  #pragma omp parallel
  {
    unsigned int id = omp_get_thread_num();
    #pragma omp for
    for ( unsigned int i=0;i<mat.n_cols;i++ )
    {
      getters[id].fixedIndx = i;
      filter.filterArray( mat, getters[id] );
    }
  }
}

void visa::Visualizer::resizeWindow( unsigned int newWidth, unsigned int newHeight )
{
  width = newWidth;
  height = newHeight;
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
  sf::Sprite sprite( *tx );
  window->draw(sprite);
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
