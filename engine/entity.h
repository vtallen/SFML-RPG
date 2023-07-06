#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>

namespace eng {
class Entity {
protected:
    sf::RectangleShape mShape;
    float mMovementSpeed{};
public:
    Entity();

    virtual ~Entity();

    virtual void move(float dt, float dirX, float dirY);

    virtual void update(float dt);
    virtual void render(sf::RenderTarget *target);
};
}

#endif
