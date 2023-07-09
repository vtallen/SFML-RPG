#include "button.h"

namespace gui {
Button::Button(float x, float y, float width, float height, sf::Font *font, std::string_view text, const sf::Color idleColor,
               const sf::Color hoverColor, const sf::Color activeColor) :
               mFont{font},
               mIdleColor{idleColor},
               mActiveColor{activeColor},
               mHoverColor{hoverColor}
{
    assert(mFont && "Button::Button() - the passed in font was nullptr");

    mState = ButtonStates::IDLE;

    mShape.setPosition(sf::Vector2f(x, y));
    mShape.setSize(sf::Vector2f(width, height));
    mShape.setFillColor(mIdleColor);

    mText.setFont(*mFont);
    mText.setString(text.data());
    mText.setFillColor(sf::Color::White);
    mText.setCharacterSize(20);

    mText.setPosition((mShape.getPosition().x / 2.f) + (mText.getGlobalBounds().width / 2.f),
                      (mShape.getPosition().y / 2.f) + (mText.getGlobalBounds().height));

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
            break;
        case HOVER:
            mShape.setFillColor(mHoverColor);
            break;
        case ACTIVE:
            mShape.setFillColor(mActiveColor);
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
