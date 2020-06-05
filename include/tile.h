//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_TILE_H
#define MONOPOLY_TILE_H

#include <string>

namespace monopoly {

class Tile {
  public:
    Tile(){};
    
    Tile(const std::string &name, int position, const std::string &group)
            : name_(name), position_(position), group_(group) {};
    
    std::string GetName() { return name_; };
    
    std::string GetGroup() { return group_; };
    
    int GetPosition() { return position_; };
    
    // find some way to return group type as an object...look into inheritance
  
  private:
    std::string name_;
    int position_;
    std::string group_;
    
  };
}

#endif //MONOPOLY_TILE_H
