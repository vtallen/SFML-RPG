#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <iostream>
#include <string>
#include <string_view>

#include "../engine/gui/button.h"

class PauseMenu {
private:
  sf::RenderWindow &mWindow;

  sf::RectangleShape mBackground;
  sf::RectangleShape mButtonBackground;

  sf::Font &mFont;
  sf::Text mPauseMenuTitle;


  std::unordered_map<std::string, gui::Button*> mButtons;

  void addButton(std::string_view key, float y, std::string_view text);

public:
/*
 * Constructor / Destructor
 */
  PauseMenu(sf::RenderWindow &window, sf::Font &font);

  virtual ~PauseMenu();
/*
 * Getters
 */
  bool isButtonPressed(std::string_view key);
  const std::unordered_map<std::string, gui::Button *> & getButtons() const;

/*
 * Functions
 */

  void update(const sf::Vector2f &mousePos);

  void render();
};


#endif
