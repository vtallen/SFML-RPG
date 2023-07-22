#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cassert>
#include <exception>
#include <map>
#include <string>
#include <stack>
#include <fstream>

#include "../engine/state.h"
#include "../engine/gui/button.h"
#include "../states/game_state.h"

class EditorState : public eng::State {
private:
  /*
   * Vars
   */
  sf::Font mFont;

  std::map<std::string, gui::Button*> mButtons;

public:
  EditorState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states);
  ~EditorState() override;

private:
  /*
   * Init functions
   */
  void initKeybinds() override;
  void initBackground();
  void initFonts();
  void initButtons();

public:
  /*
   * Getters
   */
  void endState() override;


  void updateInput(float dt) override;
  void updateButtons();
  void update(float dt) override;
  void render() override;

};

#endif
