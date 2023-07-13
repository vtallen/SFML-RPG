#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <SFML/Graphics.hpp>

namespace eng {
class MovementComponent {
private:
    sf::Sprite *mSprite;

    float mMaxVelocity;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    sf::Vector2f mDeceleration;

public:
    explicit MovementComponent(sf::Sprite &sprite, float maxVelocity);
    virtual ~MovementComponent();
    /*
     * Getters
     */

    [[nodiscard]] const sf::Vector2f &getVelocity() const;

    /*
     * Functions
     */

    void move(float x, float y, float dt);
    void update(float dt);
};
}

#endif
