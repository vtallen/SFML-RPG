#include "main_menu_state.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys) : State(window,supportedKeys) {
    assert(window && "MainMenuState::MainMenuState() - window was passed in as nullptr");
    mBackground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    mBackground.setFillColor(sf::Color::Magenta);

    initFonts();
    btn = new gui::Button{10.f, 10.f, 200.f, 50.f, &mFont, "New Game", sf::Color::Green, sf::Color::Blue, sf::Color::Red};
}

MainMenuState::~MainMenuState() {
    delete btn;
}

void MainMenuState::initKeybinds() {

}

void MainMenuState::initFonts() {
    if (!mFont.loadFromFile("../fonts/Minecraft.ttf")) {
        throw("MainMenuState::initFonts() - Unable to load ../fonts/Minecraft.ttf");
    }

}

void MainMenuState::checkForQuit() {
    State::checkForQuit();
}

void MainMenuState::endState() {

}

void MainMenuState::updateInput(float dt) {

}

void MainMenuState::update(float dt) {
    updateMousePositions();
    updateInput(dt);
    btn->update(mMousePosView);

    std::cout << mMousePosView.x << " " << mMousePosView.y << '\n';
}

void MainMenuState::render() {
    assert(mWindow && "MainMenuState::render() - mWindow was nullptr");
    mWindow->draw(mBackground);
    btn->render(mWindow);
}


