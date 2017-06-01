#ifndef COLOR_MAPS_H
#define COLOR_MAPS_H
#include <SFML/Graphics.hpp>

namespace visa
{
class Colormaps
{
public:
  /** Available colomaps */
  enum class Colormap_t {GREYSCALE, VIRIDIS, NIPY_SPECTRAL,INFERNO};
  Colormaps():active(Colormap_t::VIRIDIS){};
  void setMap( Colormap_t cmap ) { active = cmap; };
  void setColor( unsigned int indx, sf::Color &color ) const;
private:
  Colormap_t active {Colormap_t::VIRIDIS};
  static const double viridis[256][3];
  static const double nipySpectral[256][3];
  static const double inferno[256][3];
};
}; // namespace
#endif
