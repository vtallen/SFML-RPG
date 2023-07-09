// If this flag is present, certain functions will produce debug output
#define DEBUG_MODE

#include <iostream>
#include "game.h"
/*
 * TODO
 * Add a way to conditionally compile debug statements
 * Add a better system for file names / where configs are stored
 */
int main() {
    Game game{};
    game.run();

    return 0;
}
