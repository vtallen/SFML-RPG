#include "game.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
/*
 * Constructor / Destructor
 */

Game::Game() {
    initWindow();
    mDtClock.restart();
}

Game::~Game() {
    delete mWindow;
    while (!mStates.empty()) {
        delete mStates.top();
        mStates.pop();
    }

}

/*
 * Init functions
 */
void Game::initWindow() {
    std::ifstream ifs("../config/window.ini");

    sf::VideoMode windowBounds{800, 600};
    std::string title{"none"};
    unsigned int framerateLimit{120};
    bool vSyncEnabled{false};

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> framerateLimit;
        ifs >> vSyncEnabled;
    }

    ifs.close();

    mWindow = new sf::RenderWindow{windowBounds, title, sf::Style::Close | sf::Style::Titlebar};
    mWindow->setFramerateLimit(framerateLimit);
    mWindow->setVerticalSyncEnabled(vSyncEnabled);
}

void Game::initStates() {
   // mStates.push(new GameState);
}

/*
 * Public Functions
 */
void Game::run() {
    assert(mWindow && "Game::run() - mWindow was nullptr");
    while (mWindow->isOpen()) {
        updateDt();
        update();
        render();
        system("clear");
        std::cout << mDt << '\n';
    }
}

/*
 * Private Functions
 */
void Game::update() {
    updateSFMLEvents();
}

void Game::render() {
    assert(mWindow && "Game::render() - mWindow was nullptr");
    mWindow->clear();

    mWindow->display();
}

void Game::updateSFMLEvents() {
    while (mWindow->pollEvent(mEv)) {
        switch (mEv.type) {
            case sf::Event::Closed:
                mWindow->close();
                break;
            default:
                break;
        }
    }
}

void Game::updateDt() {
    /*
     * This function updates the mDt with the time it took to update and render 1 frame
     */
    mDt = mDtClock.getElapsedTime().asMicroseconds();
    mDtClock.restart();
}

#pragma clang diagnostic pop