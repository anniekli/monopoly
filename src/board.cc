//
// Created by GWC-CHC-07 on 6/1/2020.
//

#include <cinder/app/AppBase.h>
#include "board.h"
#include "property.h"


namespace monopoly {
  Board::Board(std::string &filepath) {
    infile.open(cinder::app::getAssetPath(filepath), std::ios::in);
  
    if (infile.good()) {
      for (auto& tile : j["tiles"]) {
        if (tile["group"] == "Railroad") {
        
        } else if (tile["group"] == "Special") {
        
        } else if (tile["group"] == "Utilities") {
        
        } else {
          Property property = new Property(tile["name"], tile["position"],
                  tile["price"], tile["rent"], tile["housecost"],
                  tile["group"]);
        }
      }
    }
  
  }
}