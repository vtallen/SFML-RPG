#include "game_state.h"

GameState::GameState(sf::RenderTarget *window, std::map<std::string, int> *supportedKeys) : State{window, supportedKeys} {
    initKeybinds();
}

GameState::~GameState() {

}

void GameState::initKeybinds() {
    assert(mSupportedKeys && "GameState::initKeybinds - mSupportedKeys was nullptr");
    mKeybinds.emplace("MOVE_UP", mSupportedKeys->at("W"));
    mKeybinds.emplace("MOVE_LEFT", mSupportedKeys->at("A"));
    mKeybinds.emplace("MOVE_DOWN", mSupportedKeys->at("S"));
    mKeybinds.emplace("MOVE_RIGHT", mSupportedKeys->at("D"));
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
    mPlayer.update(dt);
}

void GameState::render(sf::RenderTarget *target) {
    assert(!(target && mWindow) && "GameState::render() - Both mWindow and target are nullptr. Did you forget to set mWindow or pass in a target to render()?");
    target = (target == nullptr) ? mWindow : target;

    mPlayer.render(mWindow);
}
