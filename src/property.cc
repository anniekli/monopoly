//
// Created by GWC-CHC-07 on 6/2/2020.
//

#include "property.h"

namespace monopoly {
  int Property::GetRent() const {
    return rent_[num_houses_];
  }
  
  bool Property::BuyHouse() {
    if (num_houses_ > 5) {
      num_houses_ += 1;
      return true;
    }
    return false;
  }
  
  int Property::GetNumHouses() const {
    return num_houses_;
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