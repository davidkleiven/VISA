#include "windowHandler.hpp"
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

visa::WindowHandler::WindowHandler()
{
  window = new sf::RenderWindow(sf::VideoMode(width, height), "Armadillo Visualizer");
  window->setKeyRepeatEnabled(false);
  window->clear( sf::Color::Black );
  window->setVerticalSyncEnabled(true);
}

visa::WindowHandler::~WindowHandler()
{
  for ( unsigned int i=0;i<plots.size();i++ )
  {
    delete plots[i];
  }
  delete window;
}

void visa::WindowHandler::addPlot( const char* name )
{
  plots.push_back( new visa::Visualizer() );
  plots.back()->init(name);
  if ( active == NULL )
  {
    active = plots.back();
  }
}

void visa::WindowHandler::addLinePlot( const char* name )
{
  plots.push_back( new visa::Visualizer1D() );
  plots.back()->init(name);
  if ( active == NULL )
  {
    active = plots.back();
  }
}

visa::Visualizer& visa::WindowHandler::get( const char* name )
{
  string searchName(name);
  for ( unsigned int i=0;i<plots.size();i++ )
  {
    if ( plots[i]->getName() == searchName )
    {
      return *plots[i];
    }
  }

  string msg("No plot with name ");
  msg += searchName;
  msg += "!";
  throw ( runtime_error(msg) );
}

visa::Visualizer& visa::WindowHandler::get( unsigned int indx )
{
  if ( indx > plots.size() )
  {
    stringstream ss;
    ss << "VISA window handler: Plot with ID " << indx << " requested. But there are only " << plots.size() << " plots present!";
    throw ( runtime_error(ss.str()) );
  }
  return *plots[indx];
}

visa::Visualizer& visa::WindowHandler::getActive()
{
  if ( active == NULL )
  {
    throw (runtime_error("No active window set!"));
  }
  return *active;
}

void visa::WindowHandler::setActive( const char* name )
{
  active = &get(name);
}

void visa::WindowHandler::show()
{
  if ( active == NULL ) return;

  sf::Texture tx;
  for ( unsigned int i=0;i<plots.size();i++ )
  {
    tx.loadFromImage( plots[i]->getImg() );
    sf::Sprite spr(tx);
    rescale( spr, tx.getSize() );
    unsigned int x0, y0;
    startPos( i, x0, y0 );
    spr.setPosition( sf::Vector2f(x0,y0) );
    window->draw(spr);
  }
  window->display();
}

void visa::WindowHandler::saveImg( const char* fname )
{
  sf::Texture tx;
  tx.create( window->getSize().x, window->getSize().y );
  tx.update( *window );
  sf::Image img = tx.copyToImage();
  img.saveToFile( fname );
}

void visa::WindowHandler::clear()
{
  window->clear( sf::Color(0,0,0) );
}

void visa::WindowHandler::resetActive()
{
  for ( unsigned int i=0;i<plots.size();i++ )
  {
      active = plots[i];
      return;
  }
  active = NULL;
}

void visa::WindowHandler::setLayout( unsigned int nHor, unsigned int nVer )
{
  nImgHor = nHor;
  nImgVer = nVer;
}

void visa::WindowHandler::startPos( unsigned int plotNr, unsigned int &wStart, unsigned int &hStart ) const
{
  double stepW = static_cast<double>(width)/static_cast<double>(nImgHor);
  double stepH = static_cast<double>(height)/static_cast<double>(nImgVer);

  unsigned int row = plotNr%nImgVer;
  unsigned int col = plotNr/nImgHor;
  wStart = col*stepW;
  hStart = row*stepH;
}

void visa::WindowHandler::rescale( sf::Sprite &spr, const sf::Vector2u &origsize ) const
{
  unsigned int sizeW = width/nImgHor;
  unsigned int sizeH = height/nImgVer;
  spr.setScale( sizeW/static_cast<double>(origsize.x), sizeH/static_cast<double>(origsize.y) );
}
