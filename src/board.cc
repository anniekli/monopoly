//
// Created by GWC-CHC-07 on 6/1/2020.
//

#include <cinder/app/AppBase.h>
#include <utility.h>
#include "board.h"
#include "property.h"

namespace monopoly {
  Board::Board(std::string &filepath) {
    infile.open(cinder::app::getAssetPath(filepath), std::ios::in);
  
    if (infile.good()) {
      infile >> j;
      
      for (auto& tile : j["tiles"]) {
        Tile *my_tile;

        if (tile["group"] == "Railroad") {
        
        } else if (tile["group"] == "Special") {
        
        } else if (tile["group"] == "Utility") {
          
          my_tile = new Utility(tile["name"], tile["position"],
                  tile["price"], tile["group"]);
          
          tiles.push_back(*my_tile);
  
        } else {
          
          int rent[6];
          int rgb[3];
  
          for (int i = 0; i < 6; i++) {
            rent[i] = tile["rent"][i];
            
            if (i < 3) {
              rgb[i] = tile["rgb"][i];
            }
          }
          
          my_tile = new Property(tile["name"], tile["position"],
                  tile["price"], rent, tile["housecost"],
                  tile["group"], rgb);
          tiles.push_back(*my_tile);
  
        }
      }
    }
  }
  
  std::vector<Tile> Board::GetTiles() {
    return tiles;
  }
}