#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <SFML/Graphics.hpp>

namespace eng {
class MovementComponent {
private:
    sf::Sprite &mSprite;

    float mMaxVelocity;
    float mAcceleration;
    float mDeceleration;

    sf::Vector2f mVelocity;

public:
    explicit MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();
    /*
     * Getters
     */

    [[nodiscard]] const sf::Vector2f &getVelocity() const;
    bool isIdle() const;

    /*
     * Functions
     */

    void move(float x, float y, float dt);
    void update(float dt);
};
}

#endif
