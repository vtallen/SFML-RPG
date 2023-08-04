#include "tile_map.h"

namespace eng {
TileMap::TileMap() {
  mGridSize = 50;
  mMaxSize = {50, 50};
  mNumLayers = 5;

  // Create the columns
  mTileMap.resize(mMaxSize.x * 2);
  for (size_t x{0}; x < mMaxSize.x; ++x) {
    mTileMap.push_back(std::vector<std::vector<Tile>>{});
    mTileMap[x].resize(mMaxSize.y * 2);

    // Create the rows
    for (size_t y{0}; y < mMaxSize.y; ++y) {
      mTileMap[x].push_back(std::vector<Tile>{});

      for (size_t z{0}; z < mNumLayers; ++z) {
        mTileMap[x][y].push_back(Tile{static_cast<float>(x * mGridSize), static_cast<float>(y * mGridSize), static_cast<float>(mGridSize)});
      }
    }
  }
}

TileMap::~TileMap() {
  // Clean up the tile map's memory
}

void TileMap::update() {

}

void TileMap::render(sf::RenderTarget &target) {
  for (auto &x : mTileMap) {
    for (auto &y : x) {
      for (auto &tile: y) {
        tile.render(target);
      }
    }
  }
}
}
