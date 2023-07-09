#include "button.h"

namespace gui {
Button::Button(float x, float y, float width, float height, sf::Font *font, std::string_view text, sf::Color idleColor,
               sf::Color hoverColor, sf::Color activeColor) :
               mFont{font},
               mIdleColor{idleColor},
               mActiveColor{activeColor},
               mHoverColor{hoverColor}
{
    assert(mFont && "Button::Button() - the passed in font was nullptr");

    mShape.setPosition(sf::Vector2f(x, y));
    mShape.setSize(sf::Vector2f(width, height));
    mShape.setFillColor(mIdleColor);

    mText.setFont(*mFont);
    mText.setString(text.data());
    mText.setFillColor(sf::Color::White);
    mText.setCharacterSize(12);

    mText.setPosition((mShape.getPosition().x / 2.f) - (mText.getGlobalBounds().width / 2.f),
                      (mShape.getPosition().y / 2.f) - (mText.getGlobalBounds().height / 2.f));

}

Button::~Button() {
}
void Button::update(const sf::Vector2f &mousePos) {
    // Update the booleans for hover and pressed

    if (mShape.getGlobalBounds().contains(mousePos)) {

    }
}

void Button::render(sf::RenderTarget *target) {
    assert(target && "Button::render - target was nullptr");

    target->draw(mShape);
    target->draw(mText);
}
}
