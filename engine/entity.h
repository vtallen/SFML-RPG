#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>

#include "entity_components/movement_component.h"
#include "entity_components/animation_component.h"

namespace eng {
class Entity {
private:

protected:
    sf::Sprite *mSprite{nullptr};

    MovementComponent *mMovementComponent{nullptr};
    AnimationComponent *mAnimationComponent{nullptr};

    float mMovementSpeed{};

public:
    /*
     * Constructors / Destructors
     */
    Entity();
    virtual ~Entity();

    /*
     * Component Functions
     */
    virtual void setTexture(sf::Texture &texture);
    virtual void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
    virtual void createAnimationComponent(sf::Texture &textureSheet);

    /*
     * Public functions
     */
    virtual void setPosition(float x, float y);
    virtual void setPosition(sf::Vector2f position);

    virtual void move(float dirX, float dirY, float dt);

    virtual void update(float dt);
    virtual void render(sf::RenderTarget *target);
};
}

#endif
