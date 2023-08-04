#ifndef COMBO_BOX_H
#define COMBO_BOX_H

#include <pch.h>

#include "button.h"

namespace gui {
class ComboBox {
private:
  float mXPos;
  float mYPos;
  float mWidth;
  float mHeight;

  bool mShowList{false};
  float mKeyTime{};
  float mKeyTimeMax{0.2};

  sf::Font &mFont;

  sf::Color mIdleColor{sf::Color(255, 255, 255, 100)};
  sf::Color mHoverColor{sf::Color(255, 255, 255, 200)};
  sf::Color mActiveColor{sf::Color(255, 255, 255, 50)};


  sf::Color mTextIdleColor{sf::Color(255, 255, 255, 100)};
  sf::Color mTextHoverColor{sf::Color(255, 255, 255, 200)};
  sf::Color mTextActiveColor{sf::Color(255, 255, 255, 50)};

  sf::Color mOutlineIdleColor{sf::Color(0, 255, 255, 255)};
  sf::Color mOutlineHoverColor{sf::Color(0, 255, 255, 220)};
  sf::Color mOutlineActiveColor{sf::Color(0, 255, 255, 75)};

  unsigned int mActiveElementIndex{};
  std::vector<gui::Button *> mElements;

  void updateButtonPositions();

public:
  /*
   * Constructor / Destructor
   */
  ComboBox(float x, float y, float width, float height, sf::Font &font, std::vector<std::string> &list,
           unsigned int defaultIndex);

  virtual ~ComboBox();

  /*
   * Getters
   */
  unsigned short getSelectedId() const;

  /*
   * Setters
   */

  void setText(std::string_view);

  /*
   * Public functions
   */


  void update(sf::Vector2f &mousePos, float dt);

  void render(sf::RenderTarget &target);
};
}


#endif //RPG_ENGINE_COMBO_BOX_H
