#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <armadillo>
#include <string>
#include "colormaps.hpp"
#include "lowPassFilter.hpp"
#include "gaussianKernel.hpp"

namespace visa
{
/** Matrix visualizer using the SFML libray */
class Visualizer
{
public:
  Visualizer();
  ~Visualizer();

  /** Initialize the window handler */
  virtual void init( const char *windowName );

  /** Initialize the window handler */
  void init();

  /** Set values to visualize */
  void fillVertexArray( arma::mat &values );

  /** Set values to visualize */
  virtual void fillVertexArray( arma::vec &values ){};

  /** Checks if the window is still open */
  bool isOpen() const;

  /** Checks for events */
  bool pollEvent( sf::Event &event ) const;

  /** Close the window */
  void close(){ window->close(); };

  /** Dump image to screen */
  void display(){ window->display(); };

  /** Draw the vertex array */
  void draw();

  /** Fill the window with a black background color */
  void clear(){ window->clear(sf::Color::Black); };

  /** Set upper limit of the colorscale */
  void setColorMax( double max ){ colorMax = max; };

  /** Set the lower limit for the colorscale */
  void setColorMin( double min ){ colorMin = min; };

  /** Set both colorlimits (provided for convenience) */
  void setColorLim( double min, double max );

  /** Set color map */
  void setCmap( Colormaps::Colormap_t cm ){ cmaps.setMap(cm); };

  /** Down sample by simple averaging */
  static double average( const arma::mat &mat );

  /** Save current scene */
  sf::Image capture(){ return window->capture(); };

  /** Return the name of the plot */
  const std::string& getName() const { return name; };

  /** Set upper and lower y-limit. Only relevant for 1D plots */
  virtual void setLimits( double min, double max ){};
protected:
  sf::RenderWindow *window{NULL};
  sf::View *view{NULL};
  sf::VertexArray *vArray{NULL};
  sf::Texture *tx{NULL};
  visa::LowPassFilter filter;
  visa::GaussianKernel filterKernel;
  std::string name;
  sf::Image img;

  unsigned int width{640};
  unsigned int height{480};
  static const unsigned int defaultWidth{640};
  static const unsigned int defaultHeight{480};
  double colorMax{1.0};
  double colorMin{0.0};
  unsigned int vArrayNrow{0};
  unsigned int vArrayNcol{0};
  Colormaps cmaps;
  bool resizingEnabled{true};
  bool colorLimitsSetByUser{false};
  sf::Uint8 *pixels{NULL};

  /** Set color corresponding to value */
  void setColor( double value, sf::Color &color ) const;

  /** Run the matrix through the low pass filter */
  void filterMatrix( arma::mat &mat );

  /** Insert the positions in the vertex array */
  void fillVertexArrayPositions();

  /** Resize the window to match the matrix */
  void resizeWindow( unsigned int newWidth, unsigned int newHeight );

  /** Resize width */
  void resizeWidth( unsigned int newWidth );

  /** Resize height */
  void resizeHeight( unsigned int newHeight );

  /** Restores the default window height and width */
  void restoreDefaultWindowSize();

  /** Filter horizontally */
  void filterHorizontal( arma::mat &mat );

  /** Filter vertically */
  void filterVertical( arma::mat &mat );

  /** Set limits based on max and min value */
  void setMaxMinColors( arma::mat &mat );
};
}; // namespace
#endif
