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
      infile >> j;
      std::cout << "good" << std::endl;
      
      for (auto& tile : j["tiles"]) {
        Tile *my_tile;
        std::cout << tile["group"] << std::endl;
        if (tile["group"] == "Railroad") {
        
        } else if (tile["group"] == "Special") {
        
        } else if (tile["group"] == "Utilities") {
        
        } else {
          
          int rent[6];
          for (int i = 0; i < 6; i++) {
            rent[i] = tile["rent"][i];
          }
          
          my_tile = new Property(tile["name"], tile["position"],
                  tile["price"], rent, tile["housecost"],
                  tile["group"]);
          tiles.push_back(*my_tile);
  
        }
      }
    }
  }
  
  std::vector<Tile> Board::GetTiles() {
    return tiles;
  }
}