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
//    Tile(){};
    
    Tile(std::string name, const int position, const int price,
            std::string group)
            : name_(std::move(name)), position_(position), price_(price),
            group_(std::move(group)) {};
    
    std::string GetName() const { return name_; };
    
    std::string GetGroup() const { return group_; };
    
    int GetPosition() const { return position_; };
    
    int GetPrice() const { return price_; };
    
    virtual cinder::Rectf GetRectf() const { return {0, 0, 0, 0}; };
    
    virtual cinder::ivec2 GetTileVec() const { return cinder::ivec2(0, 0); };
  
  
  private:
    const std::string name_;
  
  protected:
    const int price_;
    const std::string group_;
    const int position_;
    float tile_size_ = cinder::app::getWindowWidth() / 13;
  };
}

#endif //MONOPOLY_TILE_H
