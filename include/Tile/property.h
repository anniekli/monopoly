//
// Created by GWC-CHC-07 on 6/2/2020.
//

#ifndef MONOPOLY_PROPERTY_H
#define MONOPOLY_PROPERTY_H

#include <cinder/Color.h>
#include <cinder/Rect.h>
#include "tile.h"

namespace monopoly {

using cinder::Color;

class Property: public Tile {
public:
  Property(const std::string &name, int position, int price, int rent[], int
  house_cost, const std::string &group, int rgb[])
          : Tile{name, position, price, group}, house_cost_(house_cost),
          num_houses_{0} {
    
    // manually copy in the arrays
    for (int i = 0; i < sizeof(rent); i++) {
      rent_[i] = rent[i];
      
      if (i < 3) {
        rgb_[i] = rgb[i];
      }
    }
  }
  
  cinder::Rectf GetRectf() const override;
  cinder::ivec2 GetTileVec() const override;
  int GetRent() const;
  int GetHouseCost() const;
  bool BuyHouse();
  int GetNumHouses() const;
  Color GetColor() const;
  
  void SetDice(int one, int two);
  void SetOwnerId(int owner);
  int GetOwnerId();

private:
  int rent_[6];
  int rgb_[3];
  const int house_cost_;
  const int mortgage_ = price_ / 2;
  
  
  int num_houses_;
  int owner_ = -1;
  int die_one;
  int die_two;
  
};
}
#endif //MONOPOLY_PROPERTY_H
