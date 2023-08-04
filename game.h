#ifndef GAME_H
#define GAME_H

#include <pch.h>

#include "engine/state.h"
#include "states/game_state.h"
#include "states/main_menu_state.h"

class Game {
private:
  class GraphicsSettings {
  public:
    /*
     * Variables
     */
    sf::VideoMode resolution;
    bool isFullscreen;
    bool vSyncEnabled;
    unsigned int frameRateLimit;
    unsigned int antialiasingLevel;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    std::string title;

    GraphicsSettings() {
      resolution = sf::VideoMode::getDesktopMode();
      isFullscreen = false;
      vSyncEnabled = false;
      contextSettings.antialiasingLevel = 0;
      videoModes = sf::VideoMode::getFullscreenModes();
    }

    void saveToFile(std::string_view path, std::string_view rootDir) {
      std::ofstream ofs(std::string(rootDir.data()) + "../config/window.ini");

      if (ofs.is_open()) {
        ofs << title;
        ofs << resolution.width << resolution.height;
        ofs << isFullscreen;
        ofs << frameRateLimit;
        ofs << vSyncEnabled;
        ofs << antialiasingLevel;
      }

      ofs.close();
    }

    void loadFromFile(std::string_view path, std::string_view rootDir) {
      std::ifstream ifs(std::string(rootDir.data()) + "../config/window.ini");
      videoModes = sf::VideoMode::getFullscreenModes();

      title = "Untitled";
      frameRateLimit = 120;
      vSyncEnabled = false;
      antialiasingLevel = 0;

      if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> resolution.width >> resolution.height;
        ifs >> isFullscreen;
        ifs >> frameRateLimit;
        ifs >> vSyncEnabled;
        ifs >> antialiasingLevel;
      }

      ifs.close();
    }
  };
  /*
   * Variables
   */

  // The directory where all game files will be stored
  std::string mRootDir{};

  // Window variables
  GraphicsSettings mGraphicsSettings{};
  sf::RenderWindow *mWindow{nullptr};
  std::vector<sf::VideoMode> mVideoModes;
  sf::ContextSettings mWindowSettings;
  bool mIsFullscreen{false};

  sf::Event mEv{};

  std::stack<eng::State *> mStates;

  // Delta time variables
  sf::Clock mDtClock;
  float mDt{0.f};

  // Keys supported by the game
  std::map<std::string, int> mSupportedKeys;

  /*
   * Update / Render Functions
   */
  void update();

  void render();

  // Polls for events
  void updateSFMLEvents();

  // Updates the delta time
  void updateDt();

  /*
   * Init Functions
   */
  void initGraphicsSettings();

  void initWindow();

  void initStates();

  void initKeys();

public:
  /*
   * Constructor / Destructors
   */
  Game(std::string_view rootDir);

  virtual ~Game();

  void run();

};

#endif
