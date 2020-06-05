//
// Created by GWC-CHC-07 on 6/2/2020.
//

#include "property.h"

namespace monopoly {
  const int Property::GetRent() {
    return rent_[num_houses_];
  }
  
  void Property::BuyHouse() {
    if (num_houses_ > 5) {
      num_houses_ += 1;
    }
  }
  
  const int Property::GetNumHouses() {
    return num_houses_;
  }
  
  const int Property::GetPrice() {
    return price_;
  }
  
  const int Property::GetHouseCost() {
    return house_cost_;
  }
}