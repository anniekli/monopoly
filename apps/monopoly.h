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
  kStart, // Start of the game
  kPlaying, // Game is currently being played
  kPlayerStart, // Start of the user's turn (used for initializing variables)
  kPlayerTurn, // Currently is the user's turn
  kRollDice, // Dice are being rolled
  kCPUTurn, // Currently is the turn of the CPUs
  kGameOver, // Game is over
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
  /**
   * Draws the tiles on the board, along with the background color
   */
  void DrawBoard();
  /**
   * Draws the pieces representing each player on the tiles
   */
  void DrawPlayerPieces();
  /**
   * Draws the dice to show their values. Also draws the animation when they
   * are rolled.
   */
  void DrawDice();
  /**
   * Draws the button that allows the user to roll the dice when it is their
   * turn
   */
  void DrawRollButton();
  void DrawBuyProperty();
  void RollDice();
  /**
   * Draws the animation moving the current player's piece.
   */
  void DrawUpdateCurrentPlayerPosition();
  void DrawPayRent();
  void BuyProperty();
  /**
   * Draws the current Chance/Community Chest card
   */
  void DrawCard();
  
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
  
  vector<Player> cpus_;
  Card* current_card_;
  
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
  
};
}  // namespace monopoly

#endif  // MONOPOLY_MONOPOLY_H_
