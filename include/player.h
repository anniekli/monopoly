//
// Created by GWC-CHC-07 on 6/7/2020.
//

#ifndef MONOPOLY_PLAYER_H
#define MONOPOLY_PLAYER_H

#include <string>
#include <Tile/tile.h>
#include <utility>
#include <vector>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

namespace monopoly {

class Player {

public:
  Player(){};
  Player(std::string name, cinder::gl::Texture2dRef piece)
    :name_(std::move(name)), piece_(std::move(piece)), money_(2000), in_jail_(false), position_(0) {};
    
  std::string GetName();
  cinder::gl::Texture2dRef GetPiece();
  void BuyProperty(Tile tile);
  void PayRent(Tile tile);
  bool IsJailed();
  int GetMoney();
  int GetPosition();
  void UpdatePosition(size_t dice_sum);
  void SetPosition(size_t position);
  void SetIsJailed(bool is_jailed);
  void AddMoney(int quantity);

private:
  
  std::string name_;
  cinder::gl::Texture2dRef piece_;
  int money_;
  std::vector<Tile> owned_properties_;
  bool in_jail_;
  size_t position_;
  size_t num_tiles_ = 40;
  
  
};
}

#endif //MONOPOLY_PLAYER_H
