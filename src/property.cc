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
    return Color(rgb_[0] / 255.0f, rgb_[1] / 255.0f, rgb_[2] / 255.0f);
  }
  
}