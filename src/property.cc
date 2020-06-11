//
// Created by GWC-CHC-07 on 6/2/2020.
//

#include <board.h>
#include "property.h"

namespace monopoly {
  int Property::GetRent() const {
    int num_owned = 0;
  
    // rent for railroads and utilities depend on number owned
    // num_owned always >=
    if (group_ == g_railroad) {
      for (auto& railroad : Board::railroad_tiles_) {
        if (railroad->owner_ == owner_) {
          num_owned++;
        }
      }
      return rent_[num_owned - 1];
    
    } else if (group_ == g_utility) {
      for (auto& utility : Board::utility_tiles_) {
        if (utility->owner_ == owner_) {
          num_owned++;
        }
      }
      
      // rent for utilities also depends on dice rolls, so be sure to set the
      // dice before getting rent!
      return rent_[num_owned - 1] * (die_one + die_two);
    }
    
    // rent for streets depends on number of houses
    return rent_[num_houses_];
  }
  
  bool Property::BuyHouse() {
    if (group_ != g_railroad && group_ != g_utility) {
      if (num_houses_ > 5) {
        num_houses_ += 1;
        return true;
      }
    }
    return false;
  }
  
  void Property::SetOwner(int owner) {
    owner_ = owner;
  }
  
  int Property::GetOwner() {
    return owner_;
  }
  
  int Property::GetNumHouses() const {
    if (group_ != g_utility && group_ != g_railroad) {
      return num_houses_;
    }
    return -1;
  }
  
  int Property::GetHouseCost() const {
    return house_cost_;
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