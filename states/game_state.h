/*
 * This is where the main game's code will live
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <map>

#include "../engine/state.h"
#include "../engine/entity.h"

class GameState : public eng::State {
private:
    eng::Entity mPlayer;
public:
    GameState(sf::RenderTarget *window, std::map<std::string, int> *supportedKeys);
    ~GameState() override;

    // Do any cleanup needed for the state
    void endState() override;

    void updateInput(float dt) override;

    void update(float dt) override;
    void render(sf::RenderTarget *target = nullptr) override;
};

#endif
