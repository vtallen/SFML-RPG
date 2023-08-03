#include "settings_state.h"
#include "game_state.h"
#include "editor_state.h"

/*
 * Constructor / Destructor
 */
SettingsState::SettingsState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states) : State(window, supportedKeys, states) {
  mVideoModes = sf::VideoMode::getFullscreenModes();

  initFonts();
  SettingsState::initKeybinds();
  initGUI();
  initText();
  initBackground();
}

SettingsState::~SettingsState() {
  for (auto &i : mButtons) delete i.second;
  for (auto &i : mComboBoxes) delete i.second;
}

/*
 * Private Functions
 */
void SettingsState::initKeybinds() {
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

void SettingsState::initFonts() {
  if (!mFont.loadFromFile("../fonts/Minecraft.ttf")) {
    std::cerr << "MainMenuState::initFonts() - Unable to load ../fonts/Minecraft.ttf\n";
  }
}

void SettingsState::initGUI() {
  mButtons["BACK"] = new gui::Button(100, 1000, 150, 50,
                                     &mFont, 20, "Quit",
                                     sf::Color(255, 255, 255, 200),
                                     sf::Color(255, 255, 255, 100),
                                     sf::Color(255, 255, 255, 255),
                                     sf::Color(70, 70, 70, 200),
                                     sf::Color(70, 70, 70, 100),
                                     sf::Color(70, 70, 70, 255));

  mButtons["APPLY"] = new gui::Button(500, 1000, 150, 50,
                                     &mFont, 20, "Apply",
                                     sf::Color(255, 255, 255, 200),
                                     sf::Color(255, 255, 255, 100),
                                     sf::Color(255, 255, 255, 255),
                                     sf::Color(70, 70, 70, 200),
                                     sf::Color(70, 70, 70, 100),
                                     sf::Color(70, 70, 70, 255));
  std::vector<std::string> list{"1920x1080", "800x600", "640x400"};

  std::vector<std::string> modesText;
  unsigned int defaultIndex{0};

  for (int i{0}; i < mVideoModes.size(); ++i) {
    modesText.push_back(std::to_string(mVideoModes.at(i).width) + "x" + std::to_string(mVideoModes.at(i).height));
    if ((mVideoModes.at(i).width == mWindow.getSize().x) && (mVideoModes.at(i).height == mWindow.getSize().y)) {
      defaultIndex = i;
    }
  }
  mComboBoxes["RESOLUTION"] = new gui::ComboBox{100, 450, 200, 50, mFont, modesText, defaultIndex};

}

void SettingsState::initText() {
  mSettingsText.setFont(mFont);
  mSettingsText.setPosition(100.f, 100.f);
  mSettingsText.setCharacterSize(30);
  mSettingsText.setFillColor(sf::Color(255, 255, 255, 200));
  mSettingsText.setString(
    "Resolution\n\n\n"
    "Fullscreen\n\n\n"
    "Antialiasing\n\n\n"
    );
}

void SettingsState::initBackground() {

  mBackground.setSize(
    sf::Vector2f(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
  mBackground.setFillColor(sf::Color::Black);

}

/*
 * Getters
 */

/*
 * Functions
 */
void SettingsState::updateInput(float dt) {

}

void SettingsState::updateGUI(const float dt) {
  assert(mStates && "MainMenuState::updateGUI() - mStates was nullptr");
  /*
   * Updates all of the buttons in the state, and implements their functionality
   */

  for (auto &button: mButtons) {
    button.second->update(mMousePosView);
  }

  if (mButtons["BACK"]->isPressed()) {
    endState();
  } else if (mButtons["APPLY"]->isPressed()) {
    // TODO Test, remove later
    mWindow.create(mVideoModes.at(mComboBoxes["RESOLUTION"]->getSelectedId()), "Test", sf::Style::Default);
  }

  for (auto &comboBox : mComboBoxes) comboBox.second->update(mMousePosView, dt);
}

void SettingsState::update(float dt) {
  updateMousePositions();
  updateInput(dt);

  updateGUI(dt);
}

void SettingsState::render() {
  mWindow.draw(mBackground);
  for (auto &button: mButtons) button.second->render(mWindow);
  for (auto &comboBox : mComboBoxes) comboBox.second->render(mWindow);

  mWindow.draw(mSettingsText);

  sf::Text mouseText;
  mouseText.setPosition(mMousePosView);
  mouseText.setFont(mFont);
  mouseText.setCharacterSize(30);
  mouseText.setString(std::to_string(mMousePosView.x) + ", " + std::to_string(mMousePosView.y));
  mWindow.draw(mouseText);
}
