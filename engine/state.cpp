#include "state.h"

namespace eng {

State::State(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states) :
    mWindow{window},
    mSupportedKeys{supportedKeys},
    mStates{states} {

    assert(supportedKeys && "State::State() - supportedKeys was nullptr");
    assert(states && "State::State() - states was nullptr");
}


bool State::getQuit() const { return mQuit; }

void State::endState() {
    std::cout << "State::endState() called\n";
    mQuit = true;
}

void State::updateMousePositions() {
    mMousePosScreen = sf::Mouse::getPosition();
    mMousePosWindow = sf::Mouse::getPosition(mWindow);
    mMousePosView = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
}
}
