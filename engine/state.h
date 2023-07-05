#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <stack>
#include <map>

namespace eng {
class State {
private:
    std::vector<sf::Texture*> mTextures;

public:
    State() = default;

    virtual ~State(){};

    virtual void update() = 0;
    virtual void render() = 0;
};
}

#endif
