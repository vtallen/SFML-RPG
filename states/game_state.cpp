#include "game_state.h"

/*
 * Constructors / Destructors
 */
GameState::GameState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states) :
        State{window, supportedKeys, states} {

    GameState::initKeybinds();
    initTextures();

    assert(mTextures["PLAYER_IDLE"] && "GameState::GameState - PLAYER_IDLE sf::Texture is nullptr in mTextures");
    mPlayer = new Player{10, 10, *mTextures["PLAYER_IDLE"]};

}

GameState::~GameState() {
    delete mPlayer;
    for (auto &texture : mTextures) {
        delete texture.second;
    }
}

/*
 * Init functions
 */
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

void GameState::initTextures() {
    mTextures["PLAYER_IDLE"] = new sf::Texture{};
    mTextures["PLAYER_IDLE"]->loadFromFile("../textures/player.png");
}

void GameState::endState() {
    std::cout << "GameState::endState() called\n";
    State::endState();
}

void GameState::updateInput(const float dt) {
    assert(mPlayer && "GameState::updateInput - mPlayer was nullptr");

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_LEFT")))) {
        mPlayer->move(-1.f, 0.f, dt);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_RIGHT")))) {
        mPlayer->move(1.f, 0.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_UP")))) {
        mPlayer->move(0.f, -1.f, dt);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("MOVE_DOWN")))) {
        mPlayer->move(0.f, 1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("CLOSE")))) {
        endState();
    }
}

void GameState::update(const float dt) {
    updateInput(dt);
    updateMousePositions();
    mPlayer->update(dt);
}

void GameState::render() {
    mPlayer->render(mWindow);
}
