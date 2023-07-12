#include "game.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
/*
 * Constructor / Destructor
 */

Game::Game() {
    initWindow();
    initKeys();
    initStates();
    mDtClock.restart();
}

Game::~Game() {
    delete mWindow;
    while (!mStates.empty()) {
        mStates.top()->endState();
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
    mStates.push(new MainMenuState(mWindow, &mSupportedKeys, &mStates));
   // mStates.push(new GameState(mWindow, &mSupportedKeys));
}

void Game::initKeys() {
    // Here we are creating a mapping of strings to the correct key in the sf::Keyboard::Key enum.
    std::ifstream ifs{"../config/supported_keys.ini"};

    if (ifs.is_open()) {
        std::string key{};
        int keyValue{};

        while (ifs >> key >> keyValue) {
            mSupportedKeys[key] = keyValue;
        }

    } else {
        std::cout << "Game::initKeys() - Unable to open config/supported_keys.ini\n";
    }

    ifs.close();
}

/*
 * Public Functions
 */
/*
 * MAIN LOOP, PROGRAM ENTRY POINT FROM MAIN
 */
void Game::run() {
    assert(mWindow && "Game::run() - mWindow was nullptr");
    while (mWindow->isOpen()) {
        updateDt();
        update();
        render();
        // system("clear");
        //std::cout << mDt << '\n';
    }
}

/*
 * Private Functions
 */
/*
 * Update functions
 */
void Game::update() {
    updateSFMLEvents();

    // Update the currently active state (the one on the top of the stack)
    if (!mStates.empty()) {
        mStates.top()->update(mDt);

        if (mStates.top()->getQuit()) {
            mStates.top()->endState();
            delete mStates.top();
            mStates.pop();
        }
    } else {
        mWindow->close();
    }
}

/*
 * This function updates the mDt with the time it took to update and render 1 frame
 */
void Game::updateDt() {
    mDt = mDtClock.getElapsedTime().asSeconds();
    mDtClock.restart();
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

/*
 * Render functions
 */
void Game::render() {
    assert(mWindow && "Game::render() - mWindow was nullptr");
    mWindow->clear();

    // Renders the currently active state (the one on the top of the stack)
    if (!mStates.empty()) {
        mStates.top()->render();
    }

    mWindow->display();
}



#pragma clang diagnostic pop