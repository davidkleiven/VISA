#ifndef WINDOW_HANDLER_H
#define WINDOW_HANDLER_H
#include "visualizer.hpp"
#include "visualizer1D.hpp"

namespace visa
{
/** Class that handles the windows */
class WindowHandler
{
public:
  WindowHandler(){};
  ~WindowHandler();

  /** Add a plot that will be displayed in a separate window */
  void addPlot( const char* name );

  /** Add a stander xy plot */
  void addLinePlot( const char* name );

  /** Get the visualization object */
  Visualizer& get( const char* name );

  /** Get plot by index */
  Visualizer& get( unsigned int indx );

  /** Get active visualization object */
  Visualizer& getActive();

  /** Number of plots */
  unsigned int nPlots() const { return plots.size(); };

  /** Set active visualization window */
  void setActive( const char* name );

  /** Show all plots */
  void show();
private:
  std::vector<Visualizer*> plots;
  Visualizer* active{NULL};

  /** If the active window is closed, this sets a new active window */
  void resetActive();
};
};
#endif
