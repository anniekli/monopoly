// Copyright (c) 2020 Annie Li. All rights reserved.

#ifndef MONOPOLY_MONOPOLY_H_
#define MONOPOLY_MONOPOLY_H_

#include <cinder/app/App.h>
#include <nlohmann/json.hpp>
#include <board.h>
#include <cinder/gl/Texture.h>
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
  void mouseDown(cinder::app::MouseEvent event) override;

private:
  void DrawBoard();
  
  Board board_;
  Player player_;
  GameState state_;
  
  std::string special = "Special";
  std::string utility = "Utility";
  std::string railroad = "Railroad";
  std::string chance = "Chance";
  std::string chest = "Community Chest";
  std::string water = "Water Works";
  std::string electricity = "Electric Company";
  
  cinder::gl::Texture2dRef railroad_img;
  cinder::gl::Texture2dRef electric_img;
  cinder::gl::Texture2dRef water_img;
  cinder::gl::Texture2dRef chance_img;
  cinder::gl::Texture2dRef chest_img;
  
  float tile_size_ = getWindowWidth() / 13;
  Color background_color = Color(191/255.0f, 219/255.0f, 174/255.0f);
};
}  // namespace monopoly

#endif  // MONOPOLY_MONOPOLY_H_
