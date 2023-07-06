#include "entity.h"

namespace eng {
    Entity::Entity() {
        mShape.setSize(sf::Vector2f(50.f, 50.f));
        mShape.setFillColor(sf::Color::White);
        mMovementSpeed = 100.f;
    }

    Entity::~Entity() {

    }

    void Entity::move(const float dt, const float dirX, const float dirY) {
        mShape.move(dirX * mMovementSpeed * dt, dirY * mMovementSpeed * dt);
    }

    void Entity::update(const float dt) {
    }

    void Entity::render(sf::RenderTarget *target) {
        assert((target) && "Entity::render() - target was nullptr");
        target->draw(mShape);
    }


}