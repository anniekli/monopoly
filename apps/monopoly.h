// Copyright (c) 2020 Annie Li. All rights reserved.

#ifndef MONOPOLY_MONOPOLY_H_
#define MONOPOLY_MONOPOLY_H_

#include <cinder/app/App.h>
#include <nlohmann/json.hpp>
#include <board.h>
#include <cinder/gl/Texture.h>
#include <cinder/Rect.h>
#include "player.h"

using std::vector;
using std::string;
using json = nlohmann::json;
using cinder::Color;

namespace monopoly {

enum class GameState {
  kStart,
  kPlaying,
  kPlayerStart,
  kPlayerTurn,
  kRollDice,
  kCPUTurn,
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
  void DrawDice();
  void DrawRollButton();
  void RollDice();
  void DrawUpdateCurrentPlayerPosition();
  
  Board board_;
  Player player_;
  GameState state_;
  
  cinder::gl::Texture2dRef railroad_img;
  cinder::gl::Texture2dRef electric_img;
  cinder::gl::Texture2dRef water_img;
  cinder::gl::Texture2dRef chance_img;
  cinder::gl::Texture2dRef chest_img;
  
  cinder::gl::Texture2dRef dog_img;
  cinder::gl::Texture2dRef iron_img;
  cinder::gl::Texture2dRef boat_img;
  cinder::gl::Texture2dRef wheelbarrow_img;
  
  float tile_size_ = getWindowWidth() / 13;
  Color background_color = Color(191/255.0f, 219/255.0f, 174/255.0f);
  cinder::Rectf roll_btn_rectf;
  bool is_dice_rolled_;
  bool is_roll_btn_clicked_;
  size_t die_one;
  size_t die_two;
  bool is_player_position_updated_;
  bool is_rent_paid_;
  bool is_card_drawn_;
  size_t num_cpu_;
  
  
  void DrawBuyProperty();
  
  void DrawPayRent();
};
}  // namespace monopoly

#endif  // MONOPOLY_MONOPOLY_H_
