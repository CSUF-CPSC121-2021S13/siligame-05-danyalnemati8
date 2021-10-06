#include "game.h"

void Game::Start() { gameScreen.ShowUntilClosed(); }

void Game::LaunchProjectiles() {
  for (int d = 0; d < opponentlist.size(); d++) {
    if (opponentlist[d]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> fresh_proj =
          std::make_unique<OpponentProjectile>(opponentlist[d]->GetX(),
                                               opponentlist[d]->GetY());
      olist_.push_back(std::move(fresh_proj));
    }
  }
}

void Game::RemoveInactive() {
  for (int d = 0; d < opponentlist.size(); d++) {
    if (opponentlist[d]->GetIsActive() == false) {
      opponentlist.erase(opponentlist.begin());
      d = d - 1;
    }
  }

  for (int d = 0; d < olist_.size(); d++) {
    if (olist_[d]->GetIsActive() == false) {
      olist_.erase(olist_.begin());
      d = d - 1;
    }
  }

  for (int d = 0; d < plist_.size(); d++) {
    if (plist_[d]->GetIsActive() == false) {
      plist_.erase(plist_.begin());
      d = d - 1;
    }
  }
}
