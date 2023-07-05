#include "game_state.h"

GameState::GameState(sf::RenderTarget *window) : State{window} {

}

GameState::~GameState() noexcept {

}

void GameState::endState() {
    std::cout << "GameState::endState() called\n";
}

void GameState::updateKeybinds(const float dt) {
    checkForQuit();
}

void GameState::update(const float dt) {
    updateKeybinds(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) std::cout << "A" << '\n';
}

void GameState::render(sf::RenderTarget *target) {
    assert(!(target && mWindow) && "GameState::render() - Both mWindow and target are nullptr. Did you forget to set mWindow or pass in a target to render()?");
}
