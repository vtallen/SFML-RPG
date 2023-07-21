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

// speedModifierCurrent and speedModifierMax are used to calculate a percentage, and play the animation
// at that percentage of the max speed
bool Animation::play(float dt, float speedModifierPercent) {
  // Update timer
  bool done = false;
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
      done = true;
      mCurrentRect.left = mStartRect.left;

    }
    mSprite.setTextureRect(mCurrentRect);
  }

  return done;
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

void AnimationComponent::play(const std::string_view key, float dt, const bool priority) {

  /*
  if (mLastAnimation != requestedAnim) {
    if (mLastAnimation != nullptr) {
      mLastAnimation->reset();
    }

    mLastAnimation = requestedAnim;
  }

  requestedAnim->play(dt, priority);
   */
  play(key, dt, 1.f, 1.f, priority);
}

void AnimationComponent::play(std::string_view key, const float dt, const float speedModifier, const float speedModifierMax,
                         const bool priority) {
  Animation *requestedAnim{mAnimations[key.data()]};
  float speedModifierPercent{speedModifier / speedModifierMax};

  assert(requestedAnim && "AnimationComponent::play() - the requested animation was nullptr\n");

  if (mPriorityAnimation) { // if there is a priority animation to play
    if (mPriorityAnimation == requestedAnim) {
      if (mLastAnimation != requestedAnim) {

        // if we are changing animations, then the previous animation needs
        // to be reset
        if (mLastAnimation != nullptr) {
          mLastAnimation->reset();
        }

        mLastAnimation = requestedAnim;
      }

      // if the priority animation is done, remove it
      if (requestedAnim->play(dt, speedModifierPercent)) {
        mPriorityAnimation = nullptr;
      }
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

void AnimationComponent::startAnimation(std::string_view animation) {

}

void AnimationComponent::pauseAnimation(std::string_view animation) {

}

void AnimationComponent::resetAnimation(std::string_view animation) {

}

}

