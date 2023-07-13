#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/entity.h"

class Player : public eng::Entity {
private:
    /*
     * Init functions
     */
    void initComponents();

public:
    /*
     * Constructors / Destructors
     */
    Player(float x, float y, sf::Texture *texture);

    ~Player() override;

    /*
     * Public functions
     */
    void update(float dt) override;

    void render(sf::RenderTarget *target) override;
};


#endif
