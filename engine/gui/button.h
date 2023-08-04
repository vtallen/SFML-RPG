#ifndef BUTTON_H
#define BUTTON_H

#include <pch.h>

namespace gui {
class Button {
  enum ButtonStates {
    IDLE,
    HOVER,
    ACTIVE,
  };

private:
  ButtonStates mState{};
  short unsigned mId{};

  sf::RectangleShape mShape;
  sf::Font *mFont;
  sf::Text mText;

  sf::Color mTextIdleColor;
  sf::Color mTextHoverColor;
  sf::Color mTextActiveColor;

  sf::Color mIdleColor;
  sf::Color mHoverColor;
  sf::Color mActiveColor;

  sf::Color mOutlineIdleColor;
  sf::Color mOutlineHoverColor;
  sf::Color mOutlineActiveColor;
public:
  Button(float x, float y, float width, float height,
         sf::Font *font, unsigned int characterSize, std::string_view text,
         const sf::Color &textIdleColor, const sf::Color &textHoverColor, const sf::Color &textActiveColor,
         const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor, short unsigned id = 0);

  Button(float x, float y, float width, float height, sf::Font *font, unsigned int characterSize);
  ~Button();

  /*
   * Getters
   */
  bool isPressed() const;
  short unsigned getId() const;

  std::string getText();

  const sf::Vector2f &getPosition();

  /*
   * Setters
   */
  void setText(std::string_view text);
  void setId(short unsigned id);

  void setPosition(const sf::Vector2f &position);
  void setPosition(float x, float y);

  void setTextColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);
  void setButtonColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);
  void setOutlineColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);

  void setOutlineThickness(float thickness);

  /*
   * Functions
   */

  /*
   * update and render
   */

  void update(const sf::Vector2f &mousePos);

  void render(sf::RenderTarget &target);

};
}
#endif
