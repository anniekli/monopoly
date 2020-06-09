//
// Created by GWC-CHC-07 on 6/9/2020.
//

#ifndef MONOPOLY_SPECIAL_H
#define MONOPOLY_SPECIAL_H
#include "tile.h"


namespace monopoly {

class Special : public Tile {

public:
  Special(const std::string &name, int position, int price,
           const std::string &group)
          : Tile{name, position, price, group} {}
};
}



#endif //MONOPOLY_SPECIAL_H
