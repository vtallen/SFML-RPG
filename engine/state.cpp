#include "state.h"

namespace eng {

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states) :
    mWindow{window},
    mSupportedKeys{supportedKeys},
    mStates{states} {

    assert(window && "State::State() - window was nullptr");
    assert(supportedKeys && "State::State() - supportedKeys was nullptr");
    assert(states && "State::State() - states was nullptr");
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
