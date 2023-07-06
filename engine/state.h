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

    std::map<std::string, int> *mSupportedKeys;

public:
    State(sf::RenderTarget *window, std::map<std::string, int> *supportedKeys);

    State(sf::RenderTarget *mWindow, std::map<std::string, int> *mSupportedKeys);

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
    virtual void endState() = 0;

    virtual void updateInput(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};
}

#endif
