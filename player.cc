#include "player.h"

void Player::Draw(graphics::Image &screen) {}

void Player::Move(const graphics::Image &screen) {}

void PlayerProjectile::Draw(graphics::Image &screen) {}

void PlayerProjectile::Move(const graphics::Image &screen) {
  if (!IsOutOfBounds(screen)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}
