#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

class Game {
private:
    /*
     * Variables
     */
    // Window variables
    sf::RenderWindow *mWindow{};

    sf::Event mEv{};

    // Delta time variables
    sf::Clock mDtClock;
    float mDt{};


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

public:
    /*
     * Constructor / Destructors
     */
    Game();
    virtual ~Game();

    void run();

};

#endif
