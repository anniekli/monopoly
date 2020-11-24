//
// Created by GWC-CHC-07 on 6/7/2020.
//

#include "player.h"

namespace monopoly {
  cinder::gl::Texture2dRef Player::GetPiece() {
    return piece_;
  }
  
  int Player::GetMoney() {
    return money_;
  }
  
  int Player::GetPosition() {
    return position_;
  }
  
  int Player::GetId() {
    return id_;
  }
  
  void Player::SetPosition(size_t position) {
    position_ = position;
  }
  
  void Player::UpdatePosition(size_t dice_sum) {
    position_ += dice_sum;
    position_ = position_ % num_tiles_;
  }
  
  void Player::AddMoney(int quantity) {
    money_ += quantity;
  }
}
  
