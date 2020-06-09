//
// Created by GWC-CHC-07 on 6/2/2020.
//

#ifndef MONOPOLY_PROPERTY_H
#define MONOPOLY_PROPERTY_H

#include <cinder/Color.h>
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
    for (int i = 0; i < 6; i++) {
      rent_[i] = rent[i];
      
      if (i < 3) {
        rgb_[i] = rgb[i];
      }
    }
  }
  
  int GetRent() const;
  int GetHouseCost() const;
  bool BuyHouse();
  int GetNumHouses() const;
  Color GetColor() const;
  

private:
  int rent_[6];
  int rgb_[3];
  const int house_cost_;
  int num_houses_;
  
};
}
#endif //MONOPOLY_PROPERTY_H
