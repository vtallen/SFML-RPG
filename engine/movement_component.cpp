#include "movement_component.h"

namespace eng {
MovementComponent::MovementComponent(const float maxVelocity) : mMaxVelocity{maxVelocity} {
}

MovementComponent::~MovementComponent() {

}

/*
 * Getters
 */
const sf::Vector2f &MovementComponent::getVelocity() const {
    return mVelocity;
}

void MovementComponent::move(const float x, const float y) {
    mVelocity.x = mMaxVelocity * x;
    mVelocity.y = mMaxVelocity * y;
}

void MovementComponent::update(const float dt) {

}
}