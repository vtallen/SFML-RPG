#include "game_state.h"

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states) :
    State{window, supportedKeys, states} {

    initKeybinds();
}

GameState::~GameState() {

}

void GameState::initKeybinds() {
    assert(mSupportedKeys && "GameState::initKeybinds - mSupportedKeys was nullptr");

    // Here we are mapping an action to a key, this allows us to change the key for the action in the future.
    std::ifstream ifs{"../config/gamestate_keybinds.ini"};

    if (ifs.is_open()) {
        std::string action{};
        std::string key{};

        while (ifs >> action >> key) {
            mKeybinds[action] = mSupportedKeys->at(key);
        }

    } else {

        std::cout << "Game::initKeys() - Unable to open config/supported_keys.ini\n";
    }

    ifs.close();
}

void GameState::endState() {
    std::cout << "GameState::endState() called\n";
}

void GameState::updateInput(const float dt) {
    checkForQuit();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_LEFT")))) {
        mPlayer.move(dt, -1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_RIGHT")))) {
        mPlayer.move(dt, 1.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_UP")))) {
        mPlayer.move(dt, 0.f, -1.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_DOWN")))) {
        mPlayer.move(dt, 0.f, 1.f);
    }
}

void GameState::update(const float dt) {
    updateInput(dt);
    updateMousePositions();
    mPlayer.update(dt);
}

void GameState::render() {
    assert(mWindow && "GameState::render() - Both mWindow and target are nullptr. Did you forget to set mWindow or pass in a target to render()?");

    mPlayer.render(mWindow);
}
