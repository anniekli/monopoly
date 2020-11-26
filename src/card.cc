//
// Created by GWC-CHC-07 on 6/18/2020.
//

#include <cinder/Color.h>
#include "Card/card.h"

namespace monopoly {
const std::string & Card::GetTitle() const {
  return title_;
}

const std::string & Card::GetType() const {
  return type_;
}

cinder::Color Card::GetColor() const {
  if (type_ == "chance") {
    // return red-orange
    return cinder::Color(1.0f, 69 / 255.0f, 0.0f);
  }
  // otherwise, return yellow
  return cinder::Color(1.0f, 1.0f, 0.0f);
}
}