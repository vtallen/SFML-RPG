#include "player.h"

/*
 * Constructors / Destructors
 */
Player::Player(const float x, const float y, sf::Texture &textureSheet) {
  Entity::setPosition(x, y);
  // mSprite->setTextureRect(sf::IntRect(16.f, 16.f, 16, 32));
  mSprite->scale(sf::Vector2f(5.f, 5.f));

  Entity::createMovementComponent(600.f, 1200.f, 3000.f);
  Entity::createAnimationComponent(textureSheet);

  mAnimationComponent->addAnimation("IDLE", 0.5, 16, 16, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK_RIGHT", 0.2, 16, 210, 16, 32, 32, 6);

}

Player::~Player() {

}

/*
 * Init functions
 */

/*
 * Public functions
 */
void Player::update(float dt) {
  Entity::update(dt);
  if (mMovementComponent->getIsMoving(MovementStates::IDLE)) {
    mAnimationComponent->play("IDLE", dt);
  } else if (mMovementComponent->getIsMoving(MovementStates::RIGHT)){
    mAnimationComponent->play("WALK_RIGHT", dt);
  }

}

void Player::render(sf::RenderTarget *target) {
  Entity::render(target);
}
