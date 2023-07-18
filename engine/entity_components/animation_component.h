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
  sf::Sprite &mSprite;

  float mAnimationTimer{};
  float mTimer{0.f};

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

  void play(float dt);

  void pause();

  void reset();
};

class AnimationComponent {
private:
  sf::Sprite &mSprite;

  std::unordered_map<std::string, eng::Animation*> mAnimations;

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

  void play(std::string_view key, float dt);

};
}
#endif
