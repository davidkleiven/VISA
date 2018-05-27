#ifndef VISUALIZER_H
#define VISUALIZER_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
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

  /** Set values to visualize. Depricated use setImg instead */
  void fillVertexArray( arma::mat &values );

  /** Creates an image from the matrix */
  void setImg( arma::mat &values );

  /** Set values to visualize */
  virtual void fillVertexArray( arma::vec &values ){};

  /** Set upper limit of the colorscale */
  void setColorMax( double max ){ colorMax = max; };

  /** Set the lower limit for the colorscale */
  void setColorMin( double min ){ colorMin = min; };

  /** Set both colorlimits (provided for convenience) */
  void setColorLim( double min, double max );

  /** Set color map */
  void setCmap( Colormaps::Colormap_t cm ){ cmaps.setMap(cm); };

  /** Sets the opacity */
  void setOpacity( double alpha );

  /** Get current image */
  const sf::Image& getImg() const { return *img; };

  /** Return the name of the plot */
  const std::string& getName() const { return name; };

  /** Returns the transparency factor */
  sf::Uint8 getAlpha() const { return alpha; };

  /** Set upper and lower y-limit. Only relevant for 1D plots */
  virtual void setLimits( double min, double max ){};

  /** True of the image can be plotted */
  bool isReady() const;
protected:
  sf::VertexArray *vArray{NULL};
  std::string name;
  sf::Image *img{NULL};

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
  sf::Uint8 alpha{255};
  unsigned int nPix{0};

  /** Set color corresponding to value */
  void setColor( double value, sf::Color &color ) const;

  /** Run the matrix through the low pass filter */
  void filterMatrix( arma::mat &mat );

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
