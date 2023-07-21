#include "player.h"
#define PLAYER_SCALE 5.f

/*
 * Constructors / Destructors
 */
Player::Player(const float x, const float y, sf::Texture &textureSheet) {
  Entity::setPosition(x, y);
  // mSprite->setTextureRect(sf::IntRect(16.f, 16.f, 16, 32));
  mSprite->scale(sf::Vector2f(5.f, 5.f));

  Entity::createHitboxComponenet(*mSprite, 10, 35, 65.f, 90.f);
  Entity::createMovementComponent(400.f, 10.f, 500.f);
  Entity::createAnimationComponent(textureSheet);

  mAnimationComponent->addAnimation("IDLE_DOWN", 0.5, 16, 16, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("IDLE_SIDE", 0.5, 16, 64, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("IDLE_UP", 0.5, 16, 112, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK", 0.1, 16, 208, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK_UP", 0.2, 16, 256, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK_DOWN", 0.2, 16, 160, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("ATTACK_FRONT", 0.1, 12, 311, 28, 32, 20, 4);

}

Player::~Player() = default;

/*
 * Init functions
 */

/*
 * Public functions
 */
void Player::update(float dt) {
  mMovementComponent->update(dt);
  mHitboxComponent->update();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
    mIsAttacking = true;
  }

  if (mIsAttacking) {
    if (mLastDirection == Direction::LEFT) {
      mAnimationComponent->play("ATTACK_FRONT", dt, true);
    }
  }

  if (mMovementComponent->isIdle()) {
    switch (mLastDirection) {
      case Direction::LEFT:
        mSprite->setScale(-PLAYER_SCALE, PLAYER_SCALE);
        mAnimationComponent->play("IDLE_SIDE", dt, false);
        break;
      case Direction::RIGHT:
        mSprite->setScale(PLAYER_SCALE, PLAYER_SCALE);
        mAnimationComponent->play("IDLE_SIDE", dt, false);
        break;
      case Direction::UP:
        mAnimationComponent->play("IDLE_UP", dt, false);
        break;
      case Direction::DOWN:
        mAnimationComponent->play("IDLE_DOWN", dt, false);
        break;
    }
  } else if (mMovementComponent->isMovingRight()) {
    mLastDirection = Direction::RIGHT;

    mSprite->setOrigin(0, 0);
    mSprite->setScale(PLAYER_SCALE, PLAYER_SCALE);
    mAnimationComponent->play("WALK", dt, mMovementComponent->getVelocity().x, mMovementComponent->getMaxVelocity(), false);

  } else if (mMovementComponent->isMovingLeft()) {
    mLastDirection = Direction::LEFT;

    mSprite->setOrigin(16.f, 0);
    mSprite->setScale(-PLAYER_SCALE, PLAYER_SCALE);
    mAnimationComponent->play("WALK", dt, false);

  } else if (mMovementComponent->isMovingUp()) {
    mLastDirection = Direction::UP;

    mAnimationComponent->play("WALK_UP", dt, false);

  } else if (mMovementComponent->isMovingDown()) {
    mLastDirection = Direction::DOWN;

    mAnimationComponent->play("WALK_DOWN", dt, false);
  }

}

void Player::render(sf::RenderTarget &target) {
  Entity::render(target);
  mHitboxComponent->render(target);
}
