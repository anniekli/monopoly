//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_TILE_H
#define MONOPOLY_TILE_H

#include <string>
#include <cinder/Rect.h>
#include <cinder/app/App.h>


namespace monopoly {

class Tile {
  public:
    Tile();
    
    Tile(std::string name, int position, int price,
            std::string group)
            : name_(name), position_(position), price_(price),
            group_(group) {};

    Tile(Tile&) = default;
    
    std::string GetName() const { return name_; };
    
    std::string GetGroup() const { return group_; };
    
    int GetPosition() const { return position_; };
    
    int GetPrice() const { return price_; };
    
    virtual cinder::Rectf GetRectf() const { return {0, 0, 0, 0}; };
    
    virtual cinder::ivec2 GetTileVec() const { return cinder::ivec2(0, 0); };
  
  
  private:
    std::string name_;
  
  protected:
    int price_;
    std::string group_;
    int position_;
    const float tile_size_ = cinder::app::getWindowWidth() / 13;
  };
}

#endif //MONOPOLY_TILE_H
