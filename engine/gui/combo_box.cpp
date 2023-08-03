#include "combo_box.h"

namespace gui {
/*
 * Constructor / Destructor
 */
ComboBox::ComboBox(float x, float y, float width, float height, sf::Font &font, std::vector<std::string> &list,
                   const unsigned int defaultIndex) :
  mFont{font},
  mActiveElementIndex{defaultIndex},
  mXPos{x},
  mYPos{y},
  mWidth{width},
  mHeight{height} {


  float buttonNum{1.f};
  for (int i{0}; i < list.size(); ++i) {
    if (i == mActiveElementIndex) {
      mElements.push_back(new Button{mXPos, mYPos, mWidth, mHeight, &mFont, 20, list.at(i), mTextIdleColor, mTextHoverColor, mTextActiveColor, mIdleColor, mHoverColor, mActiveColor, i});
      mElements.back()->setOutlineColor(mOutlineIdleColor, mOutlineHoverColor, mOutlineActiveColor);
      continue;
    }

    mElements.push_back(new Button{mXPos, mYPos + (buttonNum * mHeight), mWidth, mHeight, &mFont, 20, list.at(i), mTextIdleColor, mTextHoverColor, mTextActiveColor, mIdleColor, mHoverColor, mActiveColor, i});
    mElements.back()->setOutlineColor(sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
    buttonNum += 1.f;
  }

  assert(!(defaultIndex >= list.size()) && "ComboBox::ComboBox - defaultIndex is out of bounds of list");

}

ComboBox::~ComboBox() {
  for (Button *button: mElements) {
    delete button;
  }
}
/*
 * Private Functions
 */
/*
 * This function is triggered when a new active element is selected, so that it will always appear at the top
 */
void ComboBox::updateButtonPositions() {
  mElements.at(mActiveElementIndex)->setPosition(mXPos, mYPos);
  mElements.at(mActiveElementIndex)->setOutlineColor(mOutlineIdleColor, mOutlineHoverColor, mOutlineActiveColor);

  float buttonNum{1.f};
  for (int i{0}; i < mElements.size(); ++i) {
    if (i == mActiveElementIndex) {
      continue;
    }

    mElements.at(i)->setPosition(mXPos, mYPos + (buttonNum * mHeight));
    mElements.at(i)->setOutlineColor(sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
    buttonNum += 1.f;
  }
}

/*
 * Getters
 */
unsigned short ComboBox::getSelectedId() const {
  return mElements.at(mActiveElementIndex)->getId();
}

/*
 * Setters
 */

/*
 * Public functions
 */
void ComboBox::update(sf::Vector2f &mousePos, float dt) {
  mKeyTime += dt;

  if (mElements.at(mActiveElementIndex)->isPressed() && (mKeyTime >= mKeyTimeMax)) {
    if (mShowList) {
      mShowList = false;
    } else {
      mShowList = true;
    }

    mKeyTime = 0.f;
  }

  /*
   * Check if a new option has been selected, if so, switch the active element and update button positions
   */
  for (int i{0}; i < mElements.size(); ++i) {
    if (mElements.at(i)->isPressed() && (mKeyTime >= mKeyTimeMax)) {
      mShowList = false;
      if (i == mActiveElementIndex) {
        mKeyTime = 0.f;
        break;
      } else {
        mKeyTime = 0.f;
        mActiveElementIndex = i;
        updateButtonPositions();
        break;
      }
    }
  }

  if (mShowList) {
    for (Button *i: mElements) {
      i->update(mousePos);
    }
  } else {
    mElements.at(mActiveElementIndex)->update(mousePos);
  }
}

void ComboBox::render(sf::RenderTarget &target) {
  if (mShowList) {
    for (Button *i: mElements) {
      i->render(target);
    }
  } else {
    mElements.at(mActiveElementIndex)->render(target);
  }
}
}