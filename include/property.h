//
// Created by GWC-CHC-07 on 6/2/2020.
//

#ifndef MONOPOLY_PROPERTY_H
#define MONOPOLY_PROPERTY_H

#include "tile.h"

namespace monopoly {

class Property: public Tile {
public:
  Property(const std::string &name, int position, int price, const int
    (&rent)[6], int house_cost, const std::string &group)
          : Tile{name, position, group}, price_(price), rent_(rent),
          house_cost_(house_cost), num_houses_{0} {}
  
  const int GetPrice();
  const int GetRent();
  const int GetHouseCost();
  void BuyHouse();
  const int GetNumHouses();

private:
  const int price_;
  const int (&rent_)[6];
  const int house_cost_;
  int num_houses_;
  
};
}
#endif //MONOPOLY_PROPERTY_H
