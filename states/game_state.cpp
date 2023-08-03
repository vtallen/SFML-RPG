#include "game_state.h"

/*
 * Constructors / Destructors
 */
GameState::GameState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states) :
  State{window, supportedKeys, states} {

  GameState::initKeybinds();
  initFonts();
  initTextures();

  assert(mTextures["PLAYER_IDLE"] && "GameState::GameState - PLAYER_IDLE sf::Texture is nullptr in mTextures");
  mPlayer = new Player{10, 10, *mTextures["PLAYER_IDLE"]};

  // mPauseMenu = new PauseMenu{mWindow, mFont};
}

GameState::~GameState() {
  delete mPauseMenu;
  delete mPlayer;
  for (auto &texture: mTextures) {
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

void GameState::initFonts() {
  if (!mFont.loadFromFile("../fonts/Minecraft.ttf")) {
#ifdef SFML_DEBUG
    std::cout << "Unable to load font Minecraft.ttf from ../fonts/Minecraft.ttf\n";
#endif
  }
}

void GameState::endState() {
  std::cout << "GameState::endState() called\n";
  State::endState();
}

void GameState::updatePlayerInput(const float dt) {
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
}

void GameState::updateInput(const float dt) {
  mInputKeyTimer += dt;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("CLOSE"))) && mInputKeyTimer >= 0.5) {
    if (!mIsPaused) {
      pauseState();
      mPauseMenu = new PauseMenu{mWindow, mFont};
      mInputKeyTimer = 0.f;
    } else {
      if (mInputKeyTimer >= 0.5) {
        mInputKeyTimer = 0.f;
        delete mPauseMenu;
        unpauseState();
      }
    }
  }
}

void GameState::update(const float dt) {
  assert(mPlayer && "GameState::update - mPlayer was nullptr");
  assert(mPauseMenu && "GameState::update - mPauseMenu was nullptr");

  updateInput(dt);
  updateMousePositions();

  if (!mIsPaused) {
    updatePlayerInput(dt);
    mPlayer->update(dt);
  } else {
    mPauseMenu->update(mMousePosView);

    if (mPauseMenu->isButtonPressed("QUIT")) {
      endState();
    }
  }
}

void GameState::render() {
  assert(mPlayer && "GameState::render - mPlayer was nullptr");
  assert(mPauseMenu && "GameState::render - mPauseMenu was nullptr");

  mPlayer->render(mWindow);

  if (!mIsPaused) {
    // Code that only executes when the game is un-paused
  } else {
    // Update the pause menu
    mPauseMenu->render();
  }
}
