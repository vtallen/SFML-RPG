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

#include <pch.h>

#include <stack>

#include "entity.h"

namespace eng {
class State {
protected:
  std::stack<State *> *mStates;

  sf::RenderWindow &mWindow;
  std::map<std::string, sf::Texture *> mTextures;

  bool mQuit{false};
  bool mIsPaused{false};

  // Mouse position
  sf::Vector2i mMousePosScreen;
  sf::Vector2i mMousePosWindow;
  sf::Vector2f mMousePosView;

  // resources
  std::map<std::string, int> *mSupportedKeys;
  std::map<std::string, int> mKeybinds;

  // Functions
  virtual void initKeybinds() = 0;

public:
  State(sf::RenderWindow &window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

  virtual ~State() {};

  /*
   * Getters
   */
  [[nodiscard]] bool getQuit() const;

  [[nodiscard]] bool isPaused() const;

  /*
   * Functions
   */
  virtual void pauseState();

  virtual void unpauseState();

  // Does any cleanup needed by the state such as saving
  // This should be called before a state is deleted
  virtual void endState();

  virtual void updateMousePositions();

  virtual void updateInput(float dt) = 0;

  virtual void update(float dt) = 0;

  virtual void render() = 0;
};
}

#endif
