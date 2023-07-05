/*
 * This is where the main game's code will live
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../engine/state.h"

class GameState : public eng::State {
private:

public:
    GameState();
    ~GameState() override;

    void update() override;
    void render() override;

};

#endif
