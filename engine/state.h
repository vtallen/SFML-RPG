/*
 *
 */

#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <stack>
#include <map>

namespace eng {
class State {
private:

protected:
    sf::RenderTarget *mWindow;
    std::vector<sf::Texture*> mTextures;
    bool mQuit{false};

public:
    State(sf::RenderTarget *window = nullptr) : mWindow{window} {}

    virtual ~State(){};

    /*
     * Getters
     */
    virtual void checkForQuit();
    [[nodiscard]] bool getQuit() const;

    virtual void endState() = 0;

    virtual void updateKeybinds(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};
}

#endif
