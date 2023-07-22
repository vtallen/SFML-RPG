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
  Entity::createMovementComponent(400.f, 20.f, 1000.f);
  Entity::createAnimationComponent(textureSheet);

  mAnimationComponent->addAnimation("IDLE_UP", 0.5, 16, 112, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("IDLE_DOWN", 0.5, 16, 16, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("IDLE_SIDE", 0.5, 16, 64, 16, 32, 32, 6);

  mAnimationComponent->addAnimation("WALK_UP", 0.2, 16, 256, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK_DOWN", 0.2, 16, 160, 16, 32, 32, 6);
  mAnimationComponent->addAnimation("WALK", 0.1, 16, 208, 16, 32, 32, 6);

  mAnimationComponent->addAnimation("ATTACK_UP", 0.125, 16, 400, 28, 34, 20, 4);
  mAnimationComponent->addAnimation("ATTACK_DOWN", 0.125, 16, 305, 28, 34, 20, 4);
  mAnimationComponent->addAnimation("ATTACK_SIDE", 0.13, 12, 352, 30, 32, 18, 4);
}

Player::~Player() = default;

/*
 * Init functions
 */

/*
 * Public functions
 */
void Player::updateAttack() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
    std::cout << "Attack pressed\n";
    mLastAttackDirection = mLastDirection;
    mIsAttacking = true;
  }
}

void Player::updateAnimation(float dt) {
  /*
   * mAnimationComponent->play should only be called once per frame
   */
  if (mIsAttacking) {
    switch (mLastAttackDirection) {
      case Direction::LEFT:
      case Direction::RIGHT:
        if (mAnimationComponent->play("ATTACK_SIDE", dt, true)) {
          mLastAttackDirection = Direction::NONE;
          mIsAttacking = false;
        }
        break;
      case Direction::UP:
        if (mAnimationComponent->play("ATTACK_UP", dt, true)) {
          mLastAttackDirection = Direction::NONE;
          mIsAttacking = false;
        }
        break;
      case Direction::DOWN:
        if (mAnimationComponent->play("ATTACK_DOWN", dt, true)) {
          mLastAttackDirection = Direction::NONE;
          mIsAttacking = false;
        }
        break;
      case Direction::NONE:
        break;
    }
  } else if (mMovementComponent->isIdle()) {
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
      case Direction::NONE:
        break;
    }
  } else if (mMovementComponent->isMovingRight()) {
    if (mLastDirection != Direction::RIGHT) {
      mSprite->setScale(PLAYER_SCALE, PLAYER_SCALE);
      mSprite->setOrigin(0, 0);
    }

    mLastDirection = Direction::RIGHT;

    mAnimationComponent->play("WALK", dt, mMovementComponent->getVelocity().x, mMovementComponent->getMaxVelocity(),
                              false);

  } else if (mMovementComponent->isMovingLeft()) {
    if (mLastDirection != Direction::LEFT) {
      mSprite->setScale(-PLAYER_SCALE, PLAYER_SCALE);
      mSprite->setOrigin(16.f, 0);
    }

    mLastDirection = Direction::LEFT;

    mAnimationComponent->play("WALK", dt, false);

  } else if (mMovementComponent->isMovingUp()) {
    mLastDirection = Direction::UP;

    mAnimationComponent->play("WALK_UP", dt, false);

  } else if (mMovementComponent->isMovingDown()) {
    mLastDirection = Direction::DOWN;

    mAnimationComponent->play("WALK_DOWN", dt, false);
  }
}

void Player::update(float dt) {
  mMovementComponent->update(dt);
  mHitboxComponent->update();

  updateAttack();
  updateAnimation(dt);
}

void Player::render(sf::RenderTarget &target) {
  Entity::render(target);
  mHitboxComponent->render(target);
}
