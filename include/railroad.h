//
// Created by GWC-CHC-07 on 6/8/2020.
//

#ifndef MONOPOLY_RAILROAD_H
#define MONOPOLY_RAILROAD_H
#include "tile.h"


namespace monopoly {

class Railroad : public Tile {

public:
  Railroad(const std::string &name, int position, int price, int rent[],
          const std::string &group)
          : Tile{name, position, price, group}
          {
            // manually copy in the arrays
            for (int i = 0; i < 4; i++) {
              rent_[i] = rent[i];
            }
          }

private:
  int rent_[4];
};
}



#endif //MONOPOLY_RAILROAD_H
