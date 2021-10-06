#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    gameScreen.Initialize(width, height);
  }

  void CreateOpponents() {
    std::unique_ptr<Opponent> b =
        std::make_unique<Opponent>(gameScreen.GetWidth() * 0.5, 0);
    opponentlist.push_back(std::move(b));
  }

  void Init() {
    gameScreen.AddMouseEventListener(*this);
    gameScreen.AddAnimationEventListener(*this);

    player_.SetX(300);
    player_.SetY(400);
    CreateOpponents();
  }

  void Start();

  Player &GetPlayer() { return player_; }
  graphics::Image &GetGameScreen() { return gameScreen; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() {
    return opponentlist;
  }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return olist_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return plist_;
  }

  void MoveGameElements() {
    for (int d = 0; d < opponentlist.size(); d++) {
      if (opponentlist[d]->GetIsActive()) {
        opponentlist[d]->Move(gameScreen);
      }
    }
    for (int d = 0; d < olist_.size(); d++) {
      if (olist_[d]->GetIsActive()) {
        olist_[d]->Move(gameScreen);
      }
    }
    for (int d = 0; d < plist_.size(); d++) {
      if (plist_[d]->GetIsActive()) {
        plist_[d]->Move(gameScreen);
      }
    }
  }

  void FilterIntersections() {
    for (int d = 0; d < opponentlist.size(); d++) {
      if (opponentlist[d]->IntersectsWith(&player_)) {
        opponentlist[d]->SetIsActive(false);
        player_.SetIsActive(false);
        loses = true;
      }
    }
    for (int d = 0; d < olist_.size(); d++) {
      if (olist_[d]->IntersectsWith(&player_)) {
        olist_[d]->SetIsActive(false);
        player_.SetIsActive(false);
        loses = true;
      }
    }
    for (int d = 0; d < plist_.size(); d++) {
      for (int n = 0; n < opponentlist.size(); n++) {
        if (plist_[d]->IntersectsWith(opponentlist[n].get())) {
          plist_[d]->SetIsActive(false);
          opponentlist[n]->SetIsActive(false);
          if (player_.GetIsActive() == true) {
            p_score_ = p_score_ + 1;
          }
        }
      }
    }
  }

  void UpdateScreen() {
    std::string score_message = "score: ";
    score_message += p_score_;
    gameScreen.DrawRectangle(0, 0, gameScreen.GetWidth(),
                             gameScreen.GetHeight(), 255, 255, 255);
    gameScreen.DrawText(0, 0, score_message, 20, 0, 200, 225);
    if (loses == true) {
      gameScreen.DrawText(gameScreen.GetWidth() * 0.5,
                          gameScreen.GetHeight() * 0.25, "game over", 20, 0,
                          200, 225);
    }

    for (int d = 0; d < opponentlist.size(); d++) {
      if (opponentlist[d]->GetIsActive()) {
        opponentlist[d]->Draw(gameScreen);
      }
    }
    for (int d = 0; d < olist_.size(); d++) {
      if (olist_[d]->GetIsActive()) {
        olist_[d]->Draw(gameScreen);
      }
    }
    for (int d = 0; d < plist_.size(); d++) {
      if (plist_[d]->GetIsActive()) {
        plist_[d]->Draw(gameScreen);
      }
    }
    if (player_.GetIsActive()) {
      player_.Draw(gameScreen);
    }
  }

  void OnAnimationStep() override {
    if (opponentlist.size() == 0) {
      CreateOpponents();
    }
    MoveGameElements();
    LaunchProjectiles();
    FilterIntersections();
    RemoveInactive();
    UpdateScreen();
    gameScreen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent &event) override {
    if (event.GetX() > 0 && event.GetX() < gameScreen.GetWidth() &&
        event.GetY() > 0 && event.GetY() < gameScreen.GetHeight()) {
      player_.SetX(event.GetX() - (player_.GetWidth() * 0.5));
      player_.SetY(event.GetY() - (player_.GetHeight() * 0.5));
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> fresh_proj_b =
          std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY());
      plist_.push_back(std::move(fresh_proj_b));
    }
  }

  int GetScore() const { return p_score_; }
  bool HasLost() const { return loses; }

  void LaunchProjectiles();
  void RemoveInactive();

 private:
  int p_score_ = 0;
  bool loses = false;
  Player player_;
  graphics::Image gameScreen;
  std::vector<std::unique_ptr<Opponent>> opponentlist;
  std::vector<std::unique_ptr<OpponentProjectile>> olist_;
  std::vector<std::unique_ptr<PlayerProjectile>> plist_;
};

#endif
