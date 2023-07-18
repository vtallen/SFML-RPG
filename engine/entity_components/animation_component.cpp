#include "animation_component.h"
namespace eng {
/*
 * Animation class
 */
Animation::Animation(sf::Sprite &sprite, float animationTimer,
                                         int startFrameX, int startFrameY, int frameWidth, int frameHeight,
                                         int framePadding, int numFrames) :
  mSprite{sprite},
  mAnimationTimer{animationTimer},
  mFrameWidth{frameWidth},
  mFrameHeight{frameHeight},
  mFramePadding{framePadding},
  mNumFrames{numFrames} {

  mStartRect = sf::IntRect(startFrameX, startFrameY, mFrameWidth, mFrameHeight);
  mCurrentRect = mStartRect;
  mEndRect = sf::IntRect((mNumFrames - 1) * (mFrameWidth + mFramePadding), startFrameY, mFrameWidth, mFrameHeight);

  mSprite.setTextureRect(mStartRect);
}

Animation::~Animation() {

}

void Animation::play(float dt) {

  // Update timer
  mTimer = 10.f * dt;
  if (mTimer >= mAnimationTimer) {
    //reset timer
    mTimer = 0.f;

    // Animate
    if (mCurrentRect != mEndRect) {
      mCurrentRect.left += mFrameWidth + mFramePadding;
    } else { // Reset rect
      mCurrentRect.left = mStartRect.left;
    }

    mSprite.setTextureRect(mCurrentRect);
  }
}

void Animation::reset() {
  mTimer = 0.f;
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
  for (auto &i : mAnimations) delete i.second;
}

void AnimationComponent::play(const std::string_view key, float dt) {
  mAnimations[key.data()]->play(dt);
}

void AnimationComponent::addAnimation(std::string_view key, float animationTimer, int startFrameX, int startFrameY,
                                      int frameWidth, int frameHeight, int framePadding, int numFrames) {

  if (!mAnimations.contains(key.data())) {
    mAnimations.insert({key.data(), new Animation{mSprite, animationTimer, startFrameX, startFrameY, frameWidth, frameHeight, framePadding, numFrames}});
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

