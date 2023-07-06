#include "state.h"

namespace eng {

State::State(sf::RenderTarget *mWindow, std::map<std::string, int> *supportedKeys) : mWindow{mWindow},
                                                                                          mSupportedKeys{supportedKeys}{
}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) mQuit = true;
}

bool State::getQuit() const { return mQuit; }

}