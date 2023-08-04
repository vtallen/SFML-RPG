#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#include <pch.h>

namespace eng {
class HitboxComponent {
private:
  sf::Sprite &mSprite;
  sf::RectangleShape mHitbox;

  float mOffsetX{};
  float mOffsetY{};

public:
  HitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);

  virtual ~HitboxComponent();

  /*
   * Functions
   */
  bool checkIntersect(const sf::FloatRect &rect);

  void update();
  void render(sf::RenderTarget &target);

};
}


#endif
