#include "tile_map.h"

namespace eng {
TileMap::TileMap() {
  mGridSize = 50;
  mMaxSize = {5000, 5000};
  mNumLayers = 5;

  // Create the columns
  for (size_t x{0}; x < mMaxSize.x; ++x) {
    mTileMap.push_back(std::vector<std::vector<Tile *>>{});

    // Create the rows
    for (size_t y{0}; y < mMaxSize.y; ++y) {
      mTileMap[x].push_back(std::vector<Tile *>{});

      for (size_t z{0}; z < mNumLayers; ++z) {
        mTileMap[x][y].push_back(new Tile{});
      }
    }
  }
}

TileMap::~TileMap() {
  // Clean up the tile map's memory
  for (auto &col: mTileMap) {
    for (auto &row: col) {
      for (auto tile: row) {
        delete tile;
      }
    }
  }
}
}