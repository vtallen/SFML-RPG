#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <pch.h>

namespace eng {

class Animation {
private:
  sf::Sprite &mSprite;

  float mSecondsPerFrame{};
  float mTimer{0.f};
  bool mIsDone{false};

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
  /*
   * Animation - Getters and setters
   */
  [[nodiscard]] bool isDone() const;

  /*
   * Animation - Functions
   */
  bool play(float dt, float speedModifierPercent);
  bool play(float dt);

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
  bool isDone(std::string_view key);

  void addAnimation(std::string_view key, float animationTimer, int startFrameX, int startFrameY,
                    int frameWidth, int frameHeight, int framePadding, int numFrames);

  /*
   * Functions
   */

  void startAnimation(std::string_view animation);

  void pauseAnimation(std::string_view animation);

  void resetAnimation(std::string_view animation);

  bool play(std::string_view key, float dt, bool priority);
  bool play (std::string_view key, float dt, float speedModifier, float speedModifierMax, bool priority);
};
}
#endif
