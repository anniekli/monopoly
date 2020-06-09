//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_TILE_H
#define MONOPOLY_TILE_H

#include <string>
#include <utility>

namespace monopoly {

class Tile {
  public:
//    Tile(){};
    
    Tile(std::string name, const int position, const int price,
            std::string group)
            : name_(std::move(name)), position_(position), price_(price),
            group_(std::move(group)) {};
    
    std::string GetName() const { return name_; };
    
    std::string GetGroup() const { return group_; };
    
    int GetPosition() const { return position_; };
    
    virtual int GetPrice() const { return price_; };
    
    // find some way to return group type as an object...look into inheritance
  
  private:
    const std::string name_;
    const int position_;
    const int price_;
    const std::string group_;
    
  };
}

#endif //MONOPOLY_TILE_H
