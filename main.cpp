#include <iostream>
#include "game.h"
/*
 * TODO
 * Add a better system for file names / where configs are stored
 *  the program should test if the target directory exists, if it does, validate that files exist, otherwise create files
 * Logging
 *
 * BUGS:
 * FIND BETTER SOLUTION FOR STATE CLENUP, endState kinda sucks
 */

int main() {
    Game game{""};
    game.run();

    return 0;
}
