#include "windowHandler.hpp"
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
visa::WindowHandler::~WindowHandler()
{
  for ( unsigned int i=0;i<plots.size();i++ )
  {
    if ( plots[i]->isOpen() ) plots[i]->close();
    delete plots[i];
  }
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

  for ( unsigned int i=0;i<plots.size();i++ )
  {
    if ( plots[i]->isOpen() )
    {
      plots[i]->clear();
      plots[i]->draw();
      plots[i]->display();
    }
  }
  sf::Event event;
  while ( active->pollEvent(event) )
  {
    if ( event.type == sf::Event::Closed )
    {
      active->close();
      resetActive();
    }
  }
}

void visa::WindowHandler::resetActive()
{
  for ( unsigned int i=0;i<plots.size();i++ )
  {
    if ( plots[i]->isOpen() )
    {
      active = plots[i];
      return;
    }
  }
  active = NULL;
}
