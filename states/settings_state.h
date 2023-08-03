//
// Created by vtallen on 7/27/23.
//

#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <unordered_map>
#include <map>
#include <string_view>
#include <string>

#include "../engine/state.h"
#include "../engine/gui/button.h"
#include "../engine/gui/combo_box.h"

class SettingsState : public eng::State {
private:
  /*
  * Vars
  */
  sf::Texture mBackgroundTexture;
  sf::RectangleShape mBackground;
  sf::Font mFont;

  sf::Text mSettingsText;

  std::unordered_map<std::string, gui::Button *> mButtons;
  std::unordered_map<std::string, gui::ComboBox*> mComboBoxes;

  std::vector<sf::VideoMode> mVideoModes;

/*
 * Private Functions
 */
  void initKeybinds() override;

  void initBackground();

  void initFonts();

  void initGUI();

  void initText();

public:
/*
 * Constructor / Destructor
 */
  SettingsState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys,
                std::stack<State *> *states);

  virtual ~SettingsState();

/*
 * Getters
 */

/*
 * Functions
 */
  void updateInput(float dt) override;

  void updateGUI(float dt);

  void update(float dt) override;

  void render() override;
};


#endif
