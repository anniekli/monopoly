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
  
  size_t Player::GetPosition() {
    return position_;
  }
  
  int Player::GetId() {
    return id_;
  }
  
  size_t Player::GetNumGetOutJailCards() {
    return num_get_out_jail_cards_;
  }
  
  void Player::AddGetOutJailCard() {
    num_get_out_jail_cards_++;
  }
  
  void Player::UseGetOutJailCard() {
    if (num_get_out_jail_cards_ > 0) {
      num_get_out_jail_cards_--;
    }
  }
  
  void Player::SetIsJailed(bool is_jailed) {
    in_jail_ = is_jailed;
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
  
