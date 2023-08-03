#include "pause_menu.h"
/*
 * Constructor / Destructor
 */
PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font) : mWindow{window}, mFont{font} {
  mBackground.setSize(sf::Vector2f(
    static_cast<float>(mWindow.getSize().x),
    static_cast<float>(mWindow.getSize().y))
    );
  mBackground.setPosition(0.f, 0.f);
  mBackground.setFillColor(sf::Color(20, 20, 20, 100));

  mButtonBackground.setSize(sf::Vector2f(
    static_cast<float>(mWindow.getSize().x) / 4.f,
    static_cast<float>(mWindow.getSize().y) - 40.f)
    );
  mButtonBackground.setPosition(sf::Vector2f(
    (static_cast<float>(mWindow.getSize().x) / 2.f) - (mButtonBackground.getSize().x / 2),
    (static_cast<float>(mWindow.getSize().y) / 2.f) - (mButtonBackground.getSize().y / 2)
    ));
  mButtonBackground.setFillColor(sf::Color(20, 20, 20, 200));

  /*
   * Init text
   */
  mPauseMenuTitle.setFont(mFont);
  mPauseMenuTitle.setFillColor(sf::Color::White);
  mPauseMenuTitle.setCharacterSize(50);

  mPauseMenuTitle.setString("PAUSED");

  mPauseMenuTitle.setPosition(
    mButtonBackground.getGlobalBounds().left + (mButtonBackground.getGlobalBounds().width / 2) - (mPauseMenuTitle.getGlobalBounds().width / 2),
    mButtonBackground.getGlobalBounds().top + (mPauseMenuTitle.getGlobalBounds().height / 2)
    );

  addButton("QUIT", 900, "QUIT");
}

PauseMenu::~PauseMenu() {
  for (auto &button : mButtons) delete button.second;
}

/*
 * Private functions
 */

void PauseMenu::addButton(std::string_view key, const float y, std::string_view text) {

  constexpr float percentWidth{0.5};
  float width{mButtonBackground.getGlobalBounds().width * percentWidth};
  float height{100};
  float x{mButtonBackground.getGlobalBounds().left + (width / 2)};

  mButtons[key.data()] = new gui::Button(x, y, width, height,
                                               &mFont, 30, text.data(),
                                               sf::Color(255, 255, 255, 200),
                                               sf::Color(255, 255, 255, 100),
                                               sf::Color(255, 255, 255, 255),
                                               sf::Color(70, 70, 70, 200),
                                               sf::Color(70, 70, 70, 100),
                                               sf::Color(70, 70, 70, 255));
}


/*
 * Getters
 */
bool PauseMenu::isButtonPressed(std::string_view key) {
  assert(mButtons[key.data()] && "PauseMenu::isButtonPressed - requested button is nullptr");
  return mButtons[key.data()]->isPressed();
}

const std::unordered_map<std::string, gui::Button *> & PauseMenu::getButtons() const {
  return mButtons;
}

/*
 * Functions
 */
void PauseMenu::update(const sf::Vector2f &mousePos) {
  for (auto &i : mButtons) {
    i.second->update(mousePos);
  }
}

void PauseMenu::render() {
  mWindow.draw(mBackground);
  mWindow.draw(mButtonBackground);
  mWindow.draw(mPauseMenuTitle);

  for (auto &button : mButtons) {
    assert(button.second && "PauseMenu::render() - Button was nullptr");
    button.second->render(mWindow);
  }
}

