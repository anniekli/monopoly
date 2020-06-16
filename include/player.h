//
// Created by GWC-CHC-07 on 6/7/2020.
//

#ifndef MONOPOLY_PLAYER_H
#define MONOPOLY_PLAYER_H

#include <string>
#include <tile.h>
#include <vector>

namespace monopoly {

class Player {

public:
  Player()
    :name_(""), money_(2000), in_jail_(false), position_(0) {};
  Player(std::string name)
    :name_(name), money_(2000), in_jail_(false), position_(0) {};
  
  std::string GetName();
  void BuyProperty(Tile tile);
  void PayRent(Tile tile);
  bool IsJailed();
  int GetMoney();
  int GetPosition();
  void UpdatePosition(size_t dice_sum);
  void SetPosition(size_t position);

private:
  
  const std::string name_;
  int money_;
  std::vector<Tile> owned_properties_;
  bool in_jail_;
  size_t position_;
  const size_t num_tiles_ = 40;
  
  
};
}

#endif //MONOPOLY_PLAYER_H
