#ifndef WINDOW_HANDLER_H
#define WINDOW_HANDLER_H
#include "visualizer.hpp"

/** Class that handles the windows */
class WindowHandler
{
public:
  WindowHandler(){};
  ~WindowHandler();
  void addPlot( const char* name );
  Visualizer& get( const char* name );
  Visualizer& getActive();
  void setActive( const char* name );
  void show();
private:
  std::vector<Visualizer*> plots;
  Visualizer* active{NULL};
  void resetActive();
};
#endif
