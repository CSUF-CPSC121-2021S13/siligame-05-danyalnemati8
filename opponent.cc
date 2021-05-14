#include "opponent.h"

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  count = count + 1;
  if (count % 5 == 0) {
    std::unique_ptr<OpponentProjectile> olist_ = std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(olist_);
  } else {
    return nullptr;
  }
}

void Opponent::Move(const graphics::Image &back) {
  if (!IsOutOfBounds(back)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}

void OpponentProjectile::Draw(graphics::Image &screen) {}

void Opponent::Draw(graphics::Image &screen) {}

void OpponentProjectile::Move(const graphics::Image &screen) {
  if (!IsOutOfBounds(screen)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}


