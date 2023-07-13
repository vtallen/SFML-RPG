#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <SFML/Graphics.hpp>

namespace eng {
class MovementComponent {
private:
    float mMaxVelocity;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    sf::Vector2f mDeceleration;

public:
    explicit MovementComponent(float maxVelocity);
    virtual ~MovementComponent();
    /*
     * Getters
     */

    const sf::Vector2f &getVelocity() const;

    /*
     * Functions
     */

    void move(float x, float y);
    void update(float dt);
};
}

#endif
