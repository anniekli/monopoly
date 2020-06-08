// Copyright (c) 2020 Annie Li. All rights reserved.

#ifndef MONOPOLY_MONOPOLY_H_
#define MONOPOLY_MONOPOLY_H_

#include <cinder/app/App.h>
#include <nlohmann/json.hpp>
#include <board.h>
#include "player.h"

using std::vector;
using std::string;
using json = nlohmann::json;
using cinder::Color;

namespace monopoly {

enum class GameState {
  kStart,
  kPlaying,
  kGameOver,
};

class Monopoly : public cinder::app::App {
 public:
  Monopoly();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  
private:
  void DrawBoard();
  
  Board board_;
  Player player_;
  GameState state_;
  
  float tile_size_ = getWindowWidth() / 13;
  Color background_color = Color(191/255.0f, 219/255.0f, 174/255.0f);
};
}  // namespace monopoly

#endif  // MONOPOLY_MONOPOLY_H_
