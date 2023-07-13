#include "movement_component.h"

namespace eng {
MovementComponent::MovementComponent(sf::Sprite &sprite, const float maxVelocity) : mSprite{&sprite}, mMaxVelocity{maxVelocity} {
}

MovementComponent::~MovementComponent() {

}

/*
 * Getters
 */
const sf::Vector2f &MovementComponent::getVelocity() const {
    return mVelocity;
}

void MovementComponent::move(const float x, const float y, const float dt) {
    mVelocity.x = mMaxVelocity * x;
    mVelocity.y = mMaxVelocity * y;

    mSprite->move(mVelocity.x * dt, mVelocity.y * dt);
}

void MovementComponent::update(const float dt) {

}
}