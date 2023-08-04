#ifndef TILE_H
#define TILE_H

#include <pch.h>

namespace eng {
class Tile {
protected:
  sf::RectangleShape mShape;

public:
  /*
   * Constructors / Destructors
   */
  Tile(float x, float y, float gridSize);

  virtual ~Tile();

  void update();

  void render(sf::RenderTarget &target);
};

}
#endif
