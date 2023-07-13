#include "player.h"

/*
 * Constructors / Destructors
 */
Player::Player(const float x, const float y, sf::Texture &texture) {
    Entity::setTexture(texture);
    Entity::setPosition(x, y);

    initComponents();
}

Player::~Player() {

}

/*
 * Init functions
 */
void Player::initComponents() {
    Entity::createMovementComponent(100.f);
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
