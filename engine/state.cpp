#include "state.h"

namespace eng {
void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) mQuit = true;
}

bool State::getQuit() const { return mQuit; }
}