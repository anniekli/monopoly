//
// Created by GWC-CHC-07 on 6/6/2020.
//

#ifndef MONOPOLY_UTILITY_H
#define MONOPOLY_UTILITY_H

#include "tile.h"

namespace monopoly {

class Utility : public Tile {
public:
  Utility(const std::string &name, int position, int price, const std::string &group)
          : Tile{name, position, price, group} {}

private:

};
}

#endif //MONOPOLY_UTILITY_H
