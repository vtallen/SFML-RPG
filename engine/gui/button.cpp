#include "button.h"

namespace gui {
// TODO This constructor should be considered a war crime, fix later
Button::Button(float x, float y, float width, float height,
               sf::Font *font, unsigned int characterSize, std::string_view text,
               const sf::Color &textIdleColor, const sf::Color &textHoverColor, const sf::Color &textActiveColor,
               const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor, short unsigned id)
  :
  mFont{font},
  mTextIdleColor{textIdleColor},
  mTextHoverColor{textHoverColor},
  mTextActiveColor{textActiveColor},
  mIdleColor{idleColor},
  mActiveColor{activeColor},
  mHoverColor{hoverColor},
  mId{id} {
  assert(mFont && "Button::Button() - the passed in font was nullptr");

  mState = ButtonStates::IDLE;

  mShape.setPosition(sf::Vector2f(x, y));
  mShape.setSize(sf::Vector2f(width, height));
  mShape.setFillColor(mIdleColor);

  mText.setFont(*mFont);
  mText.setString(text.data());
  mText.setFillColor(mTextIdleColor);
  mText.setCharacterSize(characterSize);

  mText.setPosition((mShape.getPosition().x) + (mShape.getSize().x - mText.getGlobalBounds().width) / 2.f,
                    (mShape.getPosition().y) + (mShape.getSize().y - mText.getGlobalBounds().height) / 2.5);

}

Button::Button(float x, float y, float width, float height, sf::Font *font, unsigned int characterSize) {
}

Button::~Button() {

}

/*
 * Getters
 */
bool Button::isPressed() const {
  return mState == ButtonStates::ACTIVE;
}

std::string Button::getText() {
  return mText.getString();
}

short unsigned Button::getId() const {
  return mId;
}

const sf::Vector2f &Button::getPosition() {
  return mShape.getPosition();
}

/*
 * Setters
 */
void Button::setText(std::string_view text) {
  mText.setString(text.data());
}

void Button::setId(unsigned short id) {
  mId = id;
}

void Button::setPosition(float x, float y) {
  mShape.setPosition(x, y);
  mText.setPosition(x + (mShape.getSize().x - mText.getGlobalBounds().width) / 2.f,
                    y + (mShape.getSize().y - mText.getGlobalBounds().height) / 2.5);
}

void Button::setPosition(const sf::Vector2f &position) {
  setPosition(position.x, position.y);
}



void Button::setTextColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor) {
  mIdleColor = idleColor;
  mHoverColor = hoverColor;
  mActiveColor = activeColor;
}

void Button::setButtonColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor) {
  mTextIdleColor = idleColor;
  mTextHoverColor = hoverColor;
  mTextActiveColor = activeColor;
}

void Button::setOutlineColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor) {
  mShape.setOutlineThickness(5.f);
  mOutlineIdleColor = idleColor;
  mOutlineHoverColor = hoverColor;
  mOutlineActiveColor = activeColor;
}

void Button::setOutlineThickness(float thickness) {
  mShape.setOutlineThickness(thickness);
}

/*
 * Functions
 */

void Button::update(const sf::Vector2f &mousePos) {
  // Update the booleans for hover and pressed

  if (mShape.getGlobalBounds().contains(mousePos)) {
    mState = HOVER;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      mState = ACTIVE;
    }
  } else {
    mState = IDLE;
  }

  switch (mState) {
    case IDLE:
      mShape.setFillColor(mIdleColor);
      mText.setFillColor(mTextIdleColor);
      mShape.setOutlineColor(mOutlineIdleColor);
      break;
    case HOVER:
      mShape.setFillColor(mHoverColor);
      mText.setFillColor(mTextHoverColor);
      mShape.setOutlineColor(mOutlineHoverColor);
      break;
    case ACTIVE:
      mShape.setFillColor(mActiveColor);
      mText.setFillColor(mTextActiveColor);
      mShape.setOutlineColor(mOutlineActiveColor);
      break;
    default:
      std::cout << "Button::update - Enum ButtonStates not fully handled in switch\n";
      break;
  }
}

void Button::render(sf::RenderTarget &target) {
  target.draw(mShape);
  target.draw(mText);
}
}
