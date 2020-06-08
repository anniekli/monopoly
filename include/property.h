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
  Property(const std::string &name, int position, int price, const int
    (&rent)[6], int house_cost, const std::string &group, const int (&rgb)[3])
          : Tile{name, position, price, group}, rent_(rent),
          house_cost_(house_cost), rgb_(rgb), num_houses_{0} {}
  
  int GetRent() const;
  int GetHouseCost() const;
  bool BuyHouse();
  int GetNumHouses() const;
  Color GetColor() const;
  

private:
  const int (&rent_)[6];
  const int (&rgb_)[3];
  const int house_cost_;
  int num_houses_;
  
};
}
#endif //MONOPOLY_PROPERTY_H
