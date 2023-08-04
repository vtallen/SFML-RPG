/*
 * This is where the main game's code will live
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <pch.h>

#include "../engine/state.h"
#include "../engine/entity.h"
#include "../engine/tile/tile_map.h"

#include "../entities/player.h"

#include "../gui/pause_menu.h"

class GameState : public eng::State {
private:
  sf::Font mFont;

  PauseMenu *mPauseMenu;
  float mInputKeyTimer{};

  Player *mPlayer{nullptr};

  eng::TileMap mTileMap;
  /*
   * Private Update functions
   */
  void updatePlayerInput(float dt);
  void updateInput(float dt) override;

  /*
   * Init functions
   */
  void initKeybinds() override;

  void initTextures();

  void initFonts();

public:
  /*
   * Constructors / Destructors
   */
  GameState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

  ~GameState() override;

  // Do any cleanup needed for the state
  void endState() override;


  void update(float dt) override;

  void render() override;
};

#endif
