#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <pch.h>

#include "tile.h"


namespace eng {
class TileMap {
private:
  unsigned int mGridSize;
  unsigned int mNumLayers;
  sf::Vector2u mMaxSize;

  std::vector<std::vector<std::vector<Tile>>> mTileMap;
public:
  TileMap();
  virtual ~TileMap();

  void update();
  void render(sf::RenderTarget &target);
};
}

#endif //TILE_MAP_H
