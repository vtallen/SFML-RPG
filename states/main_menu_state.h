#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <pch.h>

#include <stack>

#include "../engine/state.h"
#include "../engine/gui/button.h"

#include "../states/game_state.h"
#include "editor_state.h"

class MainMenuState : public eng::State {
private:
    /*
     * Vars
     */
    sf::Texture mBackgroundTexture;
    sf::RectangleShape mBackground;
    sf::Font mFont;

    std::map<std::string, gui::Button*> mButtons;

public:
    MainMenuState(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states);
    ~MainMenuState() override;

private:
    /*
     * Init functions
     */
    void initKeybinds() override;
    void initBackground();
    void initFonts();
    void initButtons();

public:
    /*
     * Getters
     */
    void endState() override;


    void updateInput(float dt) override;
    void updateButtons();
    void update(float dt) override;
    void render() override;

protected:
};


#endif
