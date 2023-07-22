#include "animation_component.h"

namespace eng {
/*
 * Animation class
 */
Animation::Animation(sf::Sprite &sprite, float secondsPerFrame,
                     int startFrameX, int startFrameY, int frameWidth, int frameHeight,
                     int framePadding, int numFrames) :
  mSprite{sprite},
  mSecondsPerFrame{secondsPerFrame},
  mFrameWidth{frameWidth},
  mFrameHeight{frameHeight},
  mFramePadding{framePadding},
  mNumFrames{numFrames} {

  mStartRect = sf::IntRect(startFrameX, startFrameY, mFrameWidth, mFrameHeight);
  mCurrentRect = mStartRect;

  mEndRect = sf::IntRect(startFrameX + ((numFrames - 1) * (frameWidth + framePadding)), startFrameY, mFrameWidth,
                         mFrameHeight);

  mSprite.setTextureRect(mStartRect);
}

Animation::~Animation() {

}

/*
 * Animation - Getters
 */

bool Animation::isDone() const {
  return mIsDone;
}

/*
 * Animation - Functions
 */
// speedModifierCurrent and speedModifierMax are used to calculate a percentage, and play the animation
// at that percentage of the max speed
bool Animation::play(float dt, float speedModifierPercent) {
  // Update timer
  mIsDone = false;
  mTimer += speedModifierPercent * dt;

  if (mTimer >= mSecondsPerFrame) {
    //reset timer
    mTimer = 0.f;

    // Animate
    // Here we compare the left point of the current rect with that of the end rect,
    // if it is less than the end rect, move to the next frame, otherwise jump to frame 0
    if (mCurrentRect.left < mEndRect.left) {
      mCurrentRect.left += mFrameWidth + mFramePadding;
    } else { // Reset rect
      mCurrentRect.left = mStartRect.left;
      mIsDone = true;
    }
    mSprite.setTextureRect(mCurrentRect);

  }

  return mIsDone;
}

bool Animation::play(float dt) {
  return play(dt, 1.f); // Play the animation at the normal speed
}


void Animation::reset() {
  // Here we are setting the timer to the time per frame so that when animations switch there is no pause between them
  mTimer = mSecondsPerFrame;
  mCurrentRect = mStartRect;
}


/*
 * Animation Component
 */

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &textureSheet) :
  mSprite{sprite} {

  mSprite.setTexture(textureSheet);

}

AnimationComponent::~AnimationComponent() {
  // Delete all of the animations
  for (auto &i: mAnimations) delete i.second;
}

/*
 * Animation Component - Getters and Setters
 */
bool AnimationComponent::isDone(std::string_view key) {
  assert(mAnimations.contains(key.data()) && "AnimationComponent::isDone - Animation does not exist in mAnimations");
  return mAnimations[key.data()]->isDone();
}

void AnimationComponent::addAnimation(std::string_view key, float animationTimer, int startFrameX, int startFrameY,
                                      int frameWidth, int frameHeight, int framePadding, int numFrames) {

  if (!mAnimations.contains(key.data())) {
    mAnimations.insert({key.data(),
                        new Animation{mSprite, animationTimer, startFrameX, startFrameY, frameWidth, frameHeight,
                                      framePadding, numFrames}});
  }

#ifdef SFML_DEBUG
  else {
    std::cerr << "AnimationComponent::addAnimation - Animation " << key.data() << "is already in mAnimations\n";
  }
#endif
}

/*
 * Animation Component - Functions
 */
bool AnimationComponent::play(const std::string_view key, float dt, const bool priority) {
  return play(key, dt, 1.f, 1.f, priority);
}

bool AnimationComponent::play(std::string_view key, const float dt, const float speedModifier, const float speedModifierMax,
                         const bool priority) {
  Animation *requestedAnim{mAnimations[key.data()]};
  float speedModifierPercent{speedModifier / speedModifierMax};

  assert(requestedAnim && "AnimationComponent::play() - the requested animation was nullptr\n");
  if (mPriorityAnimation) { // if there is a priority animation to play, then play it and ignore the requested animation
    if (mLastAnimation != mPriorityAnimation) {
      if (mLastAnimation != nullptr) {
        mLastAnimation->reset();
      }

      mLastAnimation = mPriorityAnimation;
    }

   if (mPriorityAnimation->play(dt, speedModifierPercent)) {
     mPriorityAnimation = nullptr;
   }

  } else { // Play the requested animation if there is no priority animation
    if (priority) {
      mPriorityAnimation = requestedAnim;
    }

    if (mLastAnimation != requestedAnim) {
      if (mLastAnimation != nullptr) {
        mLastAnimation->reset();
      }

      mLastAnimation = requestedAnim;
    }

    requestedAnim->play(dt, speedModifierPercent);
  }

  return requestedAnim->isDone();
}


void AnimationComponent::startAnimation(std::string_view animation) {

}

void AnimationComponent::pauseAnimation(std::string_view animation) {

}

void AnimationComponent::resetAnimation(std::string_view animation) {

}

}

