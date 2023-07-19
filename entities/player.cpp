#include "player.h"

/*
 * Constructors / Destructors
 */
Player::Player(const float x, const float y, sf::Texture &textureSheet) {
  Entity::setPosition(x, y);
  // mSprite->setTextureRect(sf::IntRect(16.f, 16.f, 16, 32));
  mSprite->scale(sf::Vector2f(5.f, 5.f));

  Entity::createMovementComponent(140.f, 1400.f, 1000.f);
  Entity::createAnimationComponent(textureSheet);

  mAnimationComponent->addAnimation("IDLE", 0.5, 16, 16, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK_RIGHT", 0.2, 16, 209, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK_UP", 0.2, 16, 260, 16, 32, 32, 6);

}

Player::~Player() = default;

/*
 * Init functions
 */

/*
 * Public functions
 */
void Player::update(float dt) {
  Entity::update(dt);
  if (mMovementComponent->isIdle()) {
    mAnimationComponent->play("IDLE", dt);
  } else if (mMovementComponent->isMovingRight()) {
    mAnimationComponent->play("WALK_RIGHT", dt);
  } else if (mMovementComponent->isMovingUp()) {
    mAnimationComponent->play("WALK_UP", dt);
  }
}

void Player::render(sf::RenderTarget *target) {
  Entity::render(target);
}
