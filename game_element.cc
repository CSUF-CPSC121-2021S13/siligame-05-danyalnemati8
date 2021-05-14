#include "game_element.h"
#include <vector>
#include "cpputils/graphics/image.h"

void GameElement::Helper(graphics::Image &back, std::string &fah, int &x_,
                         int &y_) {
  const graphics::Color black = graphics::Color(0, 0, 0);
  graphics::Image picture;
  for (int d = 0; d < picture.GetWidth(); d++) {
    for (int n = 0; n < picture.GetHeight(); n++) {
      back.SetColor(d + x_, n + y_, picture.GetColor(d, n));
    }
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image &back) {
  if (x_ < 0 || y_ < 0 || x_ > back.GetWidth() || y_ > back.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
