//
// Created by GWC-CHC-07 on 6/2/2020.
//

#include <board.h>
#include "Tile/property.h"
#include <cinder/Rect.h>
#include <cinder/app/AppBase.h>

namespace monopoly {
  int Property::GetRent(size_t die_one, size_t die_two) const {
    int num_owned = 0;

    // rent for railroads and utilities depend on number owned
    // num_owned always >= 1 because the program shouldn't be getting rent
    // until at least one of the properties is owned
    if (group_ == g_railroad) {
      for (auto& railroad : Board::railroad_tiles_) {
        if (railroad->GetOwnerId() == owner_) {
          num_owned++;
        }
      }
      return rent_[num_owned - 1];

    } else if (group_ == g_utility) {
      for (auto& utility : Board::utility_tiles_) {
        if (utility->GetOwnerId() == owner_) {
          num_owned++;
        }
      }
      // rent for utilities also depends on dice rolls
      return rent_[num_owned - 1] * (die_one + die_two);
    }
    
    // rent for streets depends on number of houses
    return rent_[num_houses_];
  }
  
  bool Property::BuyHouse() {
    if (group_ != g_railroad && group_ != g_utility
      && num_houses_ < max_num_houses_) {
      num_houses_++;
      return true;
    }
    return false;
  }
  
  bool Property::BuyHotel() {
    if (group_ != g_railroad && group_ != g_utility
      && num_houses_ == max_num_houses_) {
      num_hotels_++;
      return true;
    }
    return false;
  }
  
  cinder::Rectf Property::GetRectf() const {
    const float width = cinder::app::getWindowWidth();
    const float height = cinder::app::getWindowHeight();
    
    cinder::Rectf rectf;
    
    if (position_ > 0 && position_ < 10) {
    
      rectf = cinder::Rectf(width - (tile_size_ * (position_ + 2)),
                    height - (tile_size_ * 2),
                    width - ((position_ + 1) * tile_size_), height);
    
    } else if (position_ > 10 && position_ < 20) {
    
      float new_pos = position_ - 10;
      rectf = cinder::Rectf(0, height - (tile_size_ * (new_pos + 2)),
                    tile_size_ * 2, height - (tile_size_ * (new_pos + 1)));
    
    } else if (position_ > 20 && position_ < 30) {
    
      float new_pos = position_ - 20;
      rectf = cinder::Rectf(tile_size_ * (new_pos + 1), 0,
                    tile_size_ * (new_pos + 2), tile_size_ * 2);
    
    } else if (position_ > 30) {
  
      float new_pos = position_ - 30;
      rectf = cinder::Rectf(width - (tile_size_ * 2),
                    tile_size_ * (new_pos + 1),
                    width, tile_size_ * (new_pos + 2));
    }
    
    return rectf;
  }
  
  cinder::ivec2 Property::GetTileVec() const {
    cinder::ivec2 size;
  
    if ((position_ > 0 && position_ < 10) ||
        (position_ > 20 && position_ < 30)) {
      size = {tile_size_, 2 * tile_size_};
    
    } else if ((position_ > 10 && position_ < 20) || (position_ > 30)) {
      size = {2 * tile_size_, tile_size_};
    }
    return size;
  }
  
  void Property::BuyProperty(int owner_id) {
    owner_ = owner_id;
  }
  
  int Property::GetOwnerId() {
    return owner_;
  }
  
  int Property::GetNumHouses() const {
    if (group_ != g_utility && group_ != g_railroad) {
      return num_houses_;
    }
    return -1;
  }
  
  int Property::GetNumHotels() const {
    if (group_ != g_utility && group_ != g_railroad) {
      return num_hotels_;
    }
    return -1;
  }
  
  size_t Property::GetBuildingCost() const {
    return building_cost_;
  }
  
  Color Property::GetColor() const {
    float rgb_temp[3];
    
    for (int i = 0; i < 3; i++) {
      if (rgb_[i] == 0) {
        rgb_temp[i] = 0;
      } else {
        rgb_temp[i] = rgb_[i] / 255.0f;
      }
    }
    return Color(rgb_temp[0], rgb_temp[1], rgb_temp[2]);
  }
  
}