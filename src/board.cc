//
// Created by GWC-CHC-07 on 6/1/2020.
//

#include <cinder/app/AppBase.h>
#include "utility.h"
#include "board.h"
#include "property.h"
#include "special.h"
#include "railroad.h"


namespace monopoly {
  Board::Board(std::string &filepath) {
    infile.open(cinder::app::getAssetPath(filepath), std::ios::in);
  
    if (infile.good()) {
      infile >> j;
      
      for (auto& tile : j["tiles"]) {
        Tile *my_tile;

        if (tile["group"] == "Railroad") {
  
          int rent[4];
          for (int i = 0; i < 4; i++) {
            rent[i] = tile["rent"][i];
          }
          
          my_tile = new Railroad(tile["name"], tile["position"],
                  tile["price"], rent, tile["group"]);
        
        } else if (tile["group"] == "Special") {
          
          my_tile = new Special(tile["name"], tile["position"], 0,
                  tile["group"]);
        
        } else if (tile["group"] == "Utility") {
          
          my_tile = new Utility(tile["name"], tile["position"],
                  tile["price"], tile["group"]);
          
        } else {
          
          int rent[6];
          int rgb[3];
  
          for (int i = 0; i < 6; i++) {
            rent[i] = tile["rent"][i];
            
            if (i < 3) {
              rgb[i] = tile["rgb"][i];
            }
          }
          
          // ignore the following error
          my_tile = new Property(tile["name"], tile["position"],
                  tile["price"], rent, tile["housecost"],
                  tile["group"], rgb);
        }
  
        tiles.push_back(my_tile);
      }
    }
  }
  
  std::vector<Tile*> Board::GetTiles() {
    return tiles;
  }
}