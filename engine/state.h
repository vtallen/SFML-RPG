/*
 * States are scenes that contain some sort of game content. Ex. Main menu, main game, inside of a game building
 *
 * They can be initialized with a pointer to a sf::RenderTarget and a map of supported keys
 * This class does not take ownership of the window, and will not delete it
 *
 * If nullptr is passed in for window, it can be instead passed into the render() function.
 */

#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <stack>
#include <map>

#include "entity.h"

namespace eng {
class State {
private:

protected:
    sf::RenderTarget *mWindow;
    std::vector<sf::Texture*> mTextures;
    bool mQuit{false};

    // resources
    std::map<std::string, int> *mSupportedKeys;
    std::map<std::string, int> mKeybinds;

    // Functions
    virtual void initKeybinds() = 0;
public:
    State(sf::RenderTarget *window, std::map<std::string, int> *supportedKeys);

    virtual ~State(){};

    /*
     * Getters
     */
    virtual void checkForQuit();
    [[nodiscard]] bool getQuit() const;


    /*
     * Functions
     */

    // Does any cleanup needed by the state such as saving
    // This should be called before a state is deleted
    virtual void endState() = 0;

    virtual void updateInput(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};
}

#endif
