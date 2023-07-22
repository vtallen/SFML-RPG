#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/entity.h"

class Player : public eng::Entity {
private:
  enum class Direction {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
  };

  /*
   * State variables
   */
  Direction mLastDirection{Direction::DOWN};
  Direction mLastAttackDirection{Direction::NONE};

  bool mIsAttacking{false};

    /*
     * Init functions
     */

public:
    /*
     * Constructors / Destructors
     */
    Player(float x, float y, sf::Texture &textureSheet);

    ~Player() override;

    /*
     * Public functions
     */
    void updateAttack();
    void updateAnimation(float dt);
    void update(float dt) override;

    void render(sf::RenderTarget &target) override;
};


#endif
