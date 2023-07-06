#include "game_state.h"

GameState::GameState(sf::RenderTarget *window, std::map<std::string, int> *supportedKeys) : State{window, supportedKeys} {

}

GameState::~GameState() {

}

void GameState::endState() {
    std::cout << "GameState::endState() called\n";
}

void GameState::updateInput(const float dt) {
    checkForQuit();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mPlayer.move(dt, -1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mPlayer.move(dt, 1.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        mPlayer.move(dt, 0.f, -1.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
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
