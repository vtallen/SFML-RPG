#include "tile.h"

namespace eng {
/*
 * Constructor / Destructor
 */
Tile::Tile(float x, float y, float gridSize) {
  mShape.setSize(sf::Vector2f(gridSize, gridSize));
  mShape.setPosition(x, y);
  mShape.setFillColor(sf::Color::Green);
  mShape.setOutlineThickness(2.f);
  mShape.setOutlineColor(sf::Color::White);

}

Tile::~Tile() {

}

void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
  target.draw(mShape);
}
}