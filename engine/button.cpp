#include "button.h"

namespace gui {
// TODO This constructor should be considered a war crime, fix later
// TODO need to enable the text color changing
Button::Button(float x, float y, float width, float height,
               sf::Font *font, unsigned int characterSize, std::string_view text,
               const sf::Color &textIdleColor, const sf::Color &textHoverColor, const sf::Color &textActiveColor,
               const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor) :
  mFont{font},
  mTextIdleColor{textIdleColor},
  mTextHoverColor{textHoverColor},
  mTextActiveColor{textActiveColor},
  mIdleColor{idleColor},
  mActiveColor{activeColor},
  mHoverColor{hoverColor} {
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

Button::~Button() {

}

/*
 * Getters
 */
bool Button::isPressed() const {
  return mState == ButtonStates::ACTIVE;
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
      break;
    case HOVER:
      mShape.setFillColor(mHoverColor);
      mText.setFillColor(mTextHoverColor);
      break;
    case ACTIVE:
      mShape.setFillColor(mActiveColor);
      mText.setFillColor(mTextActiveColor);
      break;
    default:
      std::cout << "Button::update - Enum ButtonStates not fully handled in switch\n";
      break;
  }
}

void Button::render(sf::RenderTarget *target) {
  assert(target && "Button::render - target was nullptr");

  target->draw(mShape);
  target->draw(mText);
}
}
