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
  WindowHandler();
  ~WindowHandler();

  /** Set the layout of for the plots */
  void setLayout( unsigned int nHor, unsigned int nVer );

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

  /** Stores current view */
  void saveImg( const char* filename );

  /** Clear content */
  void clear();

  /** Off-screen rendering of plots */
  void draw();

  /** Several images can be rendered offscreen via the draw function and displayed when show is called */
  void useSeparateDrawing(){ separateDrawing = true; };
private:
  sf::RenderWindow *window{NULL};
  sf::RenderTexture *rendText{NULL};
  std::vector<Visualizer*> plots;
  Visualizer* active{NULL};

  bool separateDrawing{false};

  unsigned int width{1024};
  unsigned int height{768};

  unsigned int nImgHor{1};
  unsigned int nImgVer{1};

  /** If the active window is closed, this sets a new active window */
  void resetActive();

  /** Computes the starting position */
  void startPos( unsigned int plotNr, unsigned int &wStart, unsigned int &hStart ) const;

  /** Rescales the texture */
  void rescale( sf::Sprite &spr, const sf::Vector2u &origsize ) const;
};
};
#endif
