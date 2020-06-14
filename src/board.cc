//
// Created by GWC-CHC-07 on 6/1/2020.
//

#include <cinder/app/AppBase.h>
#include "board.h"
#include "property.h"
#include "special.h"


namespace monopoly {
  std::vector<Property*> Board::railroad_tiles_ = {};
  std::vector<Property*> Board::utility_tiles_ = {};
  std::vector<Property*> Board::street_tiles_ = {};
  
  Board::Board(std::string &filepath) {
    infile.open(cinder::app::getAssetPath(filepath), std::ios::in);
  
    if (infile.good()) {
      infile >> j;
  
      int index = 0;
      for (auto& tile : j["tiles"]) {
        Tile *my_tile;

        if (tile["group"] == "Special") {
          
          my_tile = new Special(tile["name"], index, 0,
                  tile["group"]);
          
        } else {
          
          int rent[6];
          int i = 0;
          for (int rent_num : tile["rent"]) {
            rent[i] = rent_num;
            i++;
          }
          
          if (tile["group"] == g_railroad || tile["group"] == g_utility) {
            int rgb[3] = {0, 0, 0};
            my_tile = new Property(tile["name"], index,
                    tile["price"], rent, 0, tile["group"], rgb);
  
            Property *property = dynamic_cast<Property*>(my_tile);
            if (tile["group"] == g_railroad) {
              railroad_tiles_.push_back(property);
            } else {
              utility_tiles_.push_back(property);
            }
            
          } else {
            int rgb[3];
            for (int j = 0; j < 3; j++) {
              rgb[j] = tile["rgb"][j];
            }
  
            my_tile = new Property(tile["name"], index,
                    tile["price"], rent, tile["housecost"],
                    tile["group"], rgb);
  
            Property *property = dynamic_cast<Property*>(my_tile);
            street_tiles_.push_back(property);
          }
        }
  
        tiles.push_back(my_tile);
        index++;
      }
    }
  }
  
  std::vector<Tile*> Board::GetTiles() {
    return tiles;
  }
  
  Tile* Board::GetTileAtPos(int position) {
    return tiles.at(position);
  }
  
  std::vector<Property*> Board::GetStreets() const {
    return street_tiles_;
  }

  std::vector<Property*> Board::GetRailroads() const {
    return railroad_tiles_;
  }

  std::vector<Property *> Board::GetUtilities() const {
    return utility_tiles_;
  }
}