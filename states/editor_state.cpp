#include "editor_state.h"

EditorState::EditorState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys,
                         std::stack<State *> *states) :
  State{window, supportedKeys, states} {

  initFonts();
  EditorState::initKeybinds();
  initButtons();
}

EditorState::~EditorState() {
  for (auto &button: mButtons) { delete button.second; }
}

void EditorState::initKeybinds() {
  assert(mSupportedKeys && "EditorState::initKeybinds - mSupportedKeys was nullptr");

  // Here we are mapping an action to a key, this allows us to change the key for the action in the future.
  std::ifstream ifs{"../config/editor_state_keybinds.ini"};

  if (ifs.is_open()) {
    std::string action{};
    std::string key{};

    while (ifs >> action >> key) {
      mKeybinds[action] = mSupportedKeys->at(key);
    }

  } else {
    std::cout << "EditorState::initKeybinds() - Unable to open config/editor_state_keybinds.ini\n";
  }

  ifs.close();
}

void EditorState::initFonts() {
  if (!mFont.loadFromFile("../fonts/Minecraft.ttf")) {
    std::cerr << "EditorState::initFonts() - Unable to load ../fonts/Minecraft.ttf\n";
  }
}

void EditorState::initButtons() {
  /*
  mButtons["GAME_STATE_BTN"] = new gui::Button(100, 100, 150, 50,
                                               &mFont, 20, "New Game",
                                               sf::Color(255, 255, 255, 200),
                                               sf::Color(255, 255, 255, 100),
                                               sf::Color(255, 255, 255, 255),
                                               sf::Color(70, 70, 70, 200),
                                               sf::Color(70, 70, 70, 100),
                                               sf::Color(70, 70, 70, 255));

  mButtons["SETTINGS"] = new gui::Button(100, 175, 150, 50,
                                         &mFont, 20, "Settings",
                                         sf::Color(255, 255, 255, 200),
                                         sf::Color(255, 255, 255, 100),
                                         sf::Color(255, 255, 255, 255),
                                         sf::Color(70, 70, 70, 200),
                                         sf::Color(70, 70, 70, 100),
                                         sf::Color(70, 70, 70, 255));

  mButtons["EDITOR"] = new gui::Button(100, 250, 150, 50,
                                       &mFont, 20, "Editor",
                                       sf::Color(255, 255, 255, 200),
                                       sf::Color(255, 255, 255, 100),
                                       sf::Color(255, 255, 255, 255),
                                       sf::Color(70, 70, 70, 200),
                                       sf::Color(70, 70, 70, 100),
                                       sf::Color(70, 70, 70, 255));


  mButtons["EXIT"] = new gui::Button(100, 400, 150, 50,
                                     &mFont, 20, "Quit",
                                     sf::Color(255, 255, 255, 200),
                                     sf::Color(255, 255, 255, 100),
                                     sf::Color(255, 255, 255, 255),
                                     sf::Color(70, 70, 70, 200),
                                     sf::Color(70, 70, 70, 100),
                                     sf::Color(70, 70, 70, 255));
*/
}

/*
void EditorState::initBackground() {
  assert(mWindow && "EditorState::initBackground() - mWindow was nullptr");

  mBackground.setSize(
    sf::Vector2f(static_cast<float>(mWindow->getSize().x), static_cast<float>(mWindow->getSize().y)));
  mBackground.setFillColor(sf::Color::Black);

 // mBackgroundTexture.loadFromFile("../textures/bg.jpg");
  // mBackground.setTexture(&mBackgroundTexture);
}
*/

void EditorState::endState() {
  std::cout << "EditorState::endState() called\n";
  State::endState();
}

void EditorState::updateInput(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(mKeybinds.at("CLOSE")))) {
    endState();
  }
}

void EditorState::updateButtons() {
  assert(mStates && "EditorState::updateButtons() - mStates was nullptr");
  /*
   * Updates all of the buttons in the state, and implements their functionality
   */

  for (auto &button: mButtons) {
    button.second->update(mMousePosView);
  }

}

void EditorState::update(float dt) {
  updateMousePositions();
  updateInput(dt);

  updateButtons();
}

void EditorState::render() {

  // for (auto &button: mButtons) button.second->render(mWindow);

  /*
  sf::Text mouseText;
  mouseText.setPosition(mMousePosView);
  mouseText.setFont(mFont);
  mouseText.setCharacterSize(30);
  mouseText.setString(std::to_string(mMousePosView.x) + ", " + std::to_string(mMousePosView.y));
  mWindow->draw(mouseText);
   */
}