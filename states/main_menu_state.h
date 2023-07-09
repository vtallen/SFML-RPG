#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <iostream>
#include <cassert>

#include "../engine/state.h"
#include "../engine/button.h"

class MainMenuState : public eng::State {
private:
    /*
     * Vars
     */

    sf::RectangleShape mBackground;
    sf::Font mFont;

    gui::Button *btn;


    /*
     * Init functions
     */
    void initKeybinds() override;
    void initFonts();

public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys);
    ~MainMenuState() override;

    /*
     * Getters
     */
    void checkForQuit() override;
    void endState() override;


    void updateInput(float dt) override;
    void update(float dt) override;
    void render() override;

protected:
};


#endif
