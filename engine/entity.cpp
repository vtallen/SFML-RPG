#include "entity.h"

namespace eng {
/*
 * Constructors / Destructors
 */
Entity::Entity() {
    mMovementSpeed = 100.f;
}

Entity::~Entity() {
    delete mSprite;
}

/*
 * Component Functions
 */
void Entity::createSprite(sf::Texture *texture) {
    assert(texture && "Entity::createSprite - texture was nullptr");

    mSprite = new sf::Sprite{};
    mTexture = texture;
    mSprite->setTexture(*mTexture);
}

/*
 * Public functions
 */
void Entity::setPosition(const float x, const float y) {
    if (mSprite) {
        mSprite->setPosition(x, y);
    }
}

void Entity::setPosition(const sf::Vector2f position) {
    Entity::setPosition(position.x, position.y);
}

void Entity::move(const float dt, const float dirX, const float dirY) {
    if (mSprite) {
        mSprite->move(dirX * mMovementSpeed * dt, dirY * mMovementSpeed * dt);
    }
}

void Entity::update(const float dt) {
}

void Entity::render(sf::RenderTarget *target) {
    assert((target) && "Entity::render() - target was nullptr");

    if (mSprite) {
        target->draw(*mSprite);
    }
}
}