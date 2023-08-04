#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <pch.h>

namespace eng {
enum class MovementStates {
  IDLE = 0,
  MOVING,
  LEFT,
  RIGHT,
  UP,
  DOWN,
};

class MovementComponent {
private:
  sf::Sprite &mSprite;

  float mMaxVelocity;
  float mAcceleration;
  float mDeceleration;

  sf::Vector2f mVelocity;

  // This is the last direction the object was moved with the move() function.
  MovementStates mLastMovement;

public:


  explicit MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

  virtual ~MovementComponent();

  /*
   * Getters
   */
  [[nodiscard]] const sf::Vector2f &getVelocity() const;

  [[nodiscard]] float getMaxVelocity();

  [[nodiscard]] bool getIsMoving(MovementStates state) const;

  [[nodiscard]] bool isIdle() const;

  [[nodiscard]] bool isMoving() const;

  [[nodiscard]] bool isMovingLeft() const;

  [[nodiscard]] bool isMovingRight() const;

  [[nodiscard]] bool isMovingUp() const;

  [[nodiscard]] bool isMovingDown() const;

  /*
   * Functions
   */

  void move(float x, float y, float dt);

  void update(float dt);
};
}

#endif
