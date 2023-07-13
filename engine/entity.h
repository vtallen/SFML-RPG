#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>

#include "movement_component.h"

namespace eng {
class Entity {
private:

protected:
    sf::Texture *mTexture{nullptr};
    sf::Sprite *mSprite{nullptr};

    MovementComponent *mMovementComponent{nullptr};
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
    virtual void createSprite(sf::Texture *texture);
    virtual void createMovementComponent(float maxVelocity);

    /*
     * Public functions
     */
    virtual void setPosition(float x, float y);
    virtual void setPosition(sf::Vector2f position);

    virtual void move(float dt, float dirX, float dirY);

    virtual void update(float dt);
    virtual void render(sf::RenderTarget *target);
};
}

#endif
