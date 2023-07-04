#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include <vector>

namespace eng {
class State {
private:
    std::vector<sf::Texture*> mTextures;

public:
    State() = default;
    virtual ~State() = 0;

    virtual void update() = 0;
    virtual void render() = 0;
};
}

#endif
