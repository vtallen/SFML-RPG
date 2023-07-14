#include "player.h"

/*
 * Constructors / Destructors
 */
Player::Player(const float x, const float y, sf::Texture &texture) {
    Entity::setTexture(texture);
    Entity::setPosition(x, y);
    mSprite->setTextureRect(sf::IntRect(16.f, 16.f, 16, 32));
    mSprite->scale(sf::Vector2f(5.f, 5.f));

    initComponents();
}

Player::~Player() {

}

/*
 * Init functions
 */
void Player::initComponents() {
    Entity::createMovementComponent(500.f, 1000.f, 1000.f);
}

/*
 * Public functions
 */
void Player::update(float dt) {
    Entity::update(dt);
}

void Player::render(sf::RenderTarget *target) {
    Entity::render(target);
}
