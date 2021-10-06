#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <memory>
#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(const int &x, const int &y, const int width, const int &height)
      : x_(x), y_(y), width_(width), height_(height), is_active(true) {}

  int GetWidth() const { return width_; }
  int GetX() const { return x_; }
  void SetX(const int &x) { x_ = x; }

  bool IsOutOfBounds(const graphics::Image &screen);
  bool IntersectsWith(GameElement *game) {
    return !(x_ > game->GetX() + game->GetWidth() ||
             game->GetX() > GetX() + GetWidth() ||
             y_ > game->GetY() + game->GetHeight() ||
             game->GetY() > GetY() + GetHeight());
  }

  int GetHeight() const { return height_; }
  int GetY() const { return y_; }
  void SetY(const int &y) { y_ = y; }

  bool GetIsActive() const { return is_active; }
  void SetIsActive(bool bron) { is_active = bron; }

  void Helper(graphics::Image &screen, std::string &fah, int &x_, int &y_);

  virtual void Draw(graphics::Image &screen) = 0;
  virtual void Move(const graphics::Image &screen) = 0;

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active = true;
};

#endif
