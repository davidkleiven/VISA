#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <armadillo>
#include <string>
#include "colormaps.hpp"
#include "lowPassFilter.hpp"
#include "gaussianKernel.hpp"

/** Matrix visualizer using the SFML libray */
class Visualizer
{
public:
  /** Available colomaps */
  enum class Colormap_t {GREYSCALE, VIRIDIS};
  Visualizer();
  ~Visualizer();

  /** Initialize the window handler */
  void init( const char *windowName );

  /** Initialize the window handler */
  void init();

  /** Set values to visualize */
  void fillVertexArray( arma::mat &values );

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

  /** Set color map */
  void setCmap( Colormap_t cm ){ cmap = cm; };

  /** Down sample by simple averaging */
  static double average( const arma::mat &mat );

  /** Save current scene */
  sf::Image capture(){ return window->capture(); };

  const std::string& getName() const { return name; };
protected:
  sf::RenderWindow *window{NULL};
  sf::View *view{NULL};
  sf::VertexArray *vArray{NULL};
  sf::RenderTexture *tx{NULL};
  LowPassFilter filter;
  GaussianKernel filterKernel;
  std::string name;

  unsigned int width{640};
  unsigned int height{480};
  static const unsigned int defaultWidth{640};
  static const unsigned int defaultHeight{480};
  double colorMax{1.0};
  double colorMin{0.0};
  unsigned int vArrayNrow{0};
  unsigned int vArrayNcol{0};
  Colormap_t cmap{Colormap_t::VIRIDIS};
  Colormaps cmaps;
  bool resizingEnabled{true};

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
};
#endif
