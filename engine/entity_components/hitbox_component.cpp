#include "hitbox_component.h"
namespace eng {

HitboxComponent::HitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height)
  : mSprite{sprite}, mOffsetX{offsetX}, mOffsetY{offsetY} {

  mHitbox.setPosition(mSprite.getPosition().x + mOffsetX, mSprite.getPosition().y + mOffsetY);
  mHitbox.setSize(sf::Vector2f(width, height));

  mHitbox.setFillColor(sf::Color::Transparent);
  mHitbox.setOutlineColor(sf::Color::Red);
  mHitbox.setOutlineThickness(1.f);
}

HitboxComponent::~HitboxComponent() {}

bool HitboxComponent::checkIntersect(const sf::FloatRect &rect) {
  return mHitbox.getGlobalBounds().intersects(rect);
}


void HitboxComponent::update() {
  mHitbox.setPosition(mSprite.getPosition().x + mOffsetX, mSprite.getPosition().y + mOffsetY);
}

void HitboxComponent::render(sf::RenderTarget &target) {
  target.draw(mHitbox);
}
}