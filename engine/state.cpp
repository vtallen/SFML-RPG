#include "state.h"

namespace eng {

State::State(sf::RenderTarget *mWindow, std::map<std::string, int> *mSupportedKeys) : mWindow(mWindow),
                                                                                      mSupportedKeys(mSupportedKeys) {
}
void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) mQuit = true;
}

bool State::getQuit() const { return mQuit; }

}