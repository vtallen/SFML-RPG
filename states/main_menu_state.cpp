#include "main_menu_state.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states) :
    State{window,supportedKeys,states} {

    assert(window && "MainMenuState::MainMenuState() - window was passed in as nullptr");

    initFonts();
    MainMenuState::initKeybinds();
    initButtons();
    initBackground();
}

MainMenuState::~MainMenuState() {
    for (auto &button: mButtons) { delete button.second; }
}

void MainMenuState::initKeybinds() {
    assert(mSupportedKeys && "MainMenuState::initKeybinds - mSupportedKeys was nullptr");

    // Here we are mapping an action to a key, this allows us to change the key for the action in the future.
    std::ifstream ifs{"../config/main_menu_state_keybinds.ini"};

    if (ifs.is_open()) {
        std::string action{};
        std::string key{};

        while (ifs >> action >> key) {
            mKeybinds[action] = mSupportedKeys->at(key);
        }

    } else {
        std::cout << "MainMenuState::initKeybinds() - Unable to open config/main_menu_state_keybinds.ini\n";
    }

    ifs.close();
}

void MainMenuState::initFonts() {
    if (!mFont.loadFromFile("../fonts/Minecraft.ttf")) {
        std::cerr << "MainMenuState::initFonts() - Unable to load ../fonts/Minecraft.ttf\n";
    }
}

void MainMenuState::initButtons() {
    mButtons["GAME_STATE_BTN"] = new gui::Button(100, 100, 150, 50,
                                                 &mFont, "New Game",
                                                 sf::Color(70, 70, 70, 200),
                                                 sf::Color(70, 70, 70, 100),
                                                 sf::Color(70, 70, 70, 255));

    mButtons["EXIT"] = new gui::Button(100, 175, 150, 50,
                                                 &mFont, "Quit",
                                                 sf::Color(70, 70, 70, 200),
                                                 sf::Color(70, 70, 70, 100),
                                                 sf::Color(70, 70, 70, 255));
}

void MainMenuState::initBackground() {
    assert(mWindow && "MainMenuState::initBackground() - mWindow was nullptr");

    mBackground.setSize(sf::Vector2f(static_cast<float>(mWindow->getSize().x), static_cast<float>(mWindow->getSize().y)));
    mBackgroundTexture.loadFromFile("../textures/bg.jpg");
    mBackground.setTexture(&mBackgroundTexture);
}

void MainMenuState::endState() {
    std::cout << "MainMenuState::endState() called\n";
    State::endState();
}

void MainMenuState::updateInput(float dt) {

}

void MainMenuState::updateButtons() {
    assert(mStates && "MainMenuState::updateButtons() - mStates was nullptr");
    /*
     * Updates all of the buttons in the state, and implements their functionality
     */

    for (auto &button : mButtons) button.second->update(mMousePosView);

    if (mButtons["GAME_STATE_BTN"]->isPressed()) {
        mStates->push(new GameState{mWindow, mSupportedKeys, mStates});
    }

    if (mButtons["EXIT"]->isPressed()) {
     endState();
    }
}

void MainMenuState::update(float dt) {
    updateMousePositions();
    updateInput(dt);

    updateButtons();
}

void MainMenuState::render() {
    assert(mWindow && "MainMenuState::render() - mWindow was nullptr");
    mWindow->draw(mBackground);
    for (auto &button : mButtons) button.second->render(mWindow);

    sf::Text mouseText;
    mouseText.setPosition(mMousePosView);
    mouseText.setFont(mFont);
    mouseText.setCharacterSize(30);
    mouseText.setString(std::to_string(mMousePosView.x) + ", " + std::to_string(mMousePosView.y));
    mWindow->draw(mouseText);
}


