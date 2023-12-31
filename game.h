#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "engine/state.h"
#include "states/game_state.h"
#include "states/main_menu_state.h"

class Game {
private:
    /*
     * Variables
     */
    // Window variables
    sf::RenderWindow *mWindow{nullptr};
    std::vector<sf::VideoMode> mVideoModes;
    sf::ContextSettings mWindowSettings;
    bool mIsFullscreen{false};

    sf::Event mEv{};

    std::stack<eng::State*> mStates;

    // Delta time variables
    sf::Clock mDtClock;
    float mDt{0.f};

    // Keybindings
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
    void initWindow();
    void initStates();
    void initKeys();

public:
    /*
     * Constructor / Destructors
     */
    Game();
    virtual ~Game();

    void run();

};

#endif
