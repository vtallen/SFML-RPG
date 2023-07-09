#include "state.h"

namespace eng {

State::State(sf::RenderWindow *mWindow, std::map<std::string, int> *supportedKeys) : mWindow{mWindow},
                                                                                          mSupportedKeys{supportedKeys}{
}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("CLOSE")))) mQuit = true;
}

bool State::getQuit() const { return mQuit; }

void State::updateMousePositions() {
    assert(mWindow && "State::updateMousePositions() - mWindow was nullptr");
    mMousePosScreen = sf::Mouse::getPosition();
    mMousePosWindow = sf::Mouse::getPosition(*mWindow);
    mMousePosView = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
}
}
