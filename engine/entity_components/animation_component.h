#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace eng {

class Animation {
private:
  sf::Sprite &mSprite;

  float mSecondsPerFrame{};
  float mTimer{0.f};
  bool mIsDone{true};

  int mNumFrames{};
  int mFrameWidth{};
  int mFrameHeight{};
  int mFramePadding{};

  sf::IntRect mCurrentRect;
  sf::IntRect mStartRect;
  sf::IntRect mEndRect;

public:
  Animation(sf::Sprite &sprite, float secondsPerFrame, int startFrameX, int startFrameY,
            int frameWidth, int frameHeight, int framePadding, int numFrames);

  virtual ~Animation();

  bool play(float dt, float speedModifierPercent);
  bool play(float dt);

  void pause();

  void reset();
};

class AnimationComponent {
private:
  sf::Sprite &mSprite;
  Animation *mLastAnimation{nullptr};
  Animation *mPriorityAnimation{nullptr};

  std::unordered_map<std::string, eng::Animation *> mAnimations;

public:


  AnimationComponent(sf::Sprite &sprite, sf::Texture &textureSheet);

  virtual ~AnimationComponent();

  /*
   * Getters / Setters
   */

  void addAnimation(std::string_view key, float animationTimer, int startFrameX, int startFrameY,
                    int frameWidth, int frameHeight, int framePadding, int numFrames);

  void startAnimation(std::string_view animation);

  void pauseAnimation(std::string_view animation);

  void resetAnimation(std::string_view animation);

  void play(std::string_view key, float dt, bool priority);
  void play (std::string_view key, float dt, float speedModifier, float speedModifierMax, bool priority);
};
}
#endif
