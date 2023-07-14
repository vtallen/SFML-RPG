#include "movement_component.h"

namespace eng {
MovementComponent::MovementComponent(sf::Sprite &sprite, const float maxVelocity, const float acceleration,
                                     const float deceleration) :
        mSprite{sprite},
        mMaxVelocity{maxVelocity},
        mAcceleration{acceleration},
        mDeceleration{deceleration} {

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
    mVelocity.x += mAcceleration * x;
    mVelocity.y += mAcceleration * y;
}

void MovementComponent::update(const float dt) {
    /*
     * Velocity checks and deceleration in the x axis
     */
    if (mVelocity.x > 0.f) { // Check if the entity is going right
        // Check if we are over the max velocity, and if so setting the x velocity to the max velocity
        if (mVelocity.x > mMaxVelocity) {
            mVelocity.x = mMaxVelocity;
        }

        // Deceleration
        mVelocity.x -= mDeceleration * dt;
        if (mVelocity.x < 0.f) {
            mVelocity.x = 0.f;
        }

    } else if (mVelocity.x < 0.f) { // Check if the entity is going left
        // Check if we are going over the max velocity in the left direction
        if (mVelocity.x < -mMaxVelocity) {
            mVelocity.x = -mMaxVelocity;
        }

        // Deceleration
        mVelocity.x += mDeceleration * dt;
        if (mVelocity.x > 0.f) {
            mVelocity.x = 0.f;
        }
    }

    /*
     * Velocity checks and deceleration in the y axis
     */
    if (mVelocity.y > 0.f) { // Check if the entity is going down
        // Limit velocity
        if (mVelocity.y > mMaxVelocity) {
            mVelocity.y = mMaxVelocity;
        }

        // Deceleration
        mVelocity.y -= mDeceleration * dt;
        // Limit deceleration
        if (mVelocity.y < 0.f) {
            mVelocity.y = 0.f;
        }
    } else if (mVelocity.y < 0.f) { // Check if the entity is going up
        // Limit velocity
        if (mVelocity.y < -mMaxVelocity) {
            mVelocity.y = -mMaxVelocity;
        }

        // Deceleration
        mVelocity.y += mDeceleration * dt;
        // Limit deceleration
        if (mVelocity.y > 0.f) {
            mVelocity.y = 0.f;
        }
    }

    // Final move
    mSprite.move(mVelocity.x * dt, mVelocity.y * dt);
}
}