#ifndef VISUALIZER1D_H
#define VISUALIZER1D_H
#include "visualizer.hpp"

namespace visa
{
/** Class for visualizing 1D curves using the SFML library */
class Visualizer1D: public Visualizer
{
public:
  Visualizer1D(){};

  /** Initialize */
  void init( const char* windowName ) override;

  /** Set values to plot */
  void fillVertexArray( arma::vec &vec ) override;

  /** Set upper and lower limits on the y-axis */
  void setLimits( double minVal, double maxVal ) override;
private:

  /** Get pixel corresponding to the y-value */
  unsigned int getY( double value ) const;
  double max{0.0};
  double min{0.0};
  bool vertexArrayInitializedByMe{false};
};
}; // namespace
#endif
