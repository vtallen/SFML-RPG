#include "entity.h"

namespace eng {
/*
 * Constructors / Destructors
 */
Entity::Entity() : mSprite{new sf::Sprite} {
  mMovementSpeed = 100.f;
}

Entity::~Entity() {
  delete mSprite;

  delete mHitboxComponent;
  delete mMovementComponent;
  delete mAnimationComponent;
}

/*
 * Component Functions
 */
void Entity::setTexture(sf::Texture &texture) {
  mSprite->setTexture(texture);
}

void Entity::createHitboxComponenet(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height) {
  mHitboxComponent = new HitboxComponent{sprite, offsetX, offsetY, width, height};
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
  assert(mSprite && "Entity::createMovementComponent - mSprite was nullptr");

  mMovementComponent = new MovementComponent(*mSprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &textureSheet) {
  assert(mSprite && "Entity::createAnimationComponent - mSprite was nullptr");

  mAnimationComponent = new AnimationComponent{*mSprite, textureSheet};
}

/*
 * Public functions
 */
void Entity::setPosition(const float x, const float y) {
  if (mSprite) {
    mSprite->setPosition(x, y);
  }
}

void Entity::setPosition(const sf::Vector2f position) {
  Entity::setPosition(position.x, position.y);
}

void Entity::move(const float dirX, const float dirY, const float dt) {
  if (mMovementComponent) {
    mMovementComponent->move(dirX, dirY, dt); // Set velocity
  }
}

void Entity::update(const float dt) {
  if (mMovementComponent) {
    mMovementComponent->update(dt);
  }
  if (mHitboxComponent) {
    mHitboxComponent->update();
  }
}

void Entity::render(sf::RenderTarget &target) {
  target.draw(*mSprite);
}
}