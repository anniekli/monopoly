//
// Created by GWC-CHC-07 on 6/9/2020.
//

#ifndef MONOPOLY_SPECIAL_H
#define MONOPOLY_SPECIAL_H
#include "tile.h"
#include <cinder/Rect.h>


namespace monopoly {

class Special : public Tile {

public:
  Special(std::string name, int position, int price,
           std::string group)
          : Tile{name, position, price, group} {}
  
  cinder::Rectf GetRectf() const override;
  cinder::ivec2 GetTileVec() const override;
};
}



#endif //MONOPOLY_SPECIAL_H
