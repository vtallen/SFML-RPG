#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cassert>

namespace gui {
class Button {
private:
    sf::RectangleShape mShape;
    sf::Font *mFont;
    sf::Text mText;

    sf::Color mIdleColor;
    sf::Color mHoverColor;
    sf::Color mActiveColor;

public:
    Button(float x, float y, float width, float height, sf::Font *font, std::string_view text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    /*
     * Functions
     */

    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget *target);

};
}
#endif
