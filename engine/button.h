#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cassert>

namespace gui {
class Button {
    enum ButtonStates {
        IDLE,
        HOVER,
        ACTIVE,
    };

private:
    ButtonStates mState{};

    sf::RectangleShape mShape;
    sf::Font *mFont;
    sf::Text mText;

    sf::Color mTextIdleColor;
    sf::Color mTextHoverColor;
    sf::Color mTextActiveColor;

    sf::Color mIdleColor;
    sf::Color mHoverColor;
    sf::Color mActiveColor;

public:
    Button(float x, float y, float width, float height,
           sf::Font *font, unsigned int characterSize, std::string_view text,
           const sf::Color &textIdleColor, const sf::Color &textHoverColor, const sf::Color &textActiveColor,
           const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);

    ~Button();
    /*
     * Getters
     */
    bool isPressed() const;
    /*
     * Functions
     */

    /*
     * update and render
     */

    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget *target);

};
}
#endif
