//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H

#include "tile.h"
#include "property.h"
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

namespace monopoly {

extern const std::string special;
extern const std::string g_utility;
extern const std::string g_railroad;
extern const std::string chance;
extern const std::string chest;
extern const std::string water;
extern const std::string electricity;

using std::string;
using json = nlohmann::json;

class Board {

public:
  Board(){};
  Board(std::string &filepath);
  
  Tile GetTile();
  void GetChanceCard();
  std::vector<Tile*> GetTiles();
  Tile* GetTileAtPos(int position);
  std::vector<Property*> GetStreets() const;
  std::vector<Property*> GetRailroads() const;
  std::vector<Property*> GetUtilities() const;
  friend class Property;

private:
  
  std::ifstream infile;
  json j;
  std::vector<Tile*> tiles;
  static std::vector<Property*> railroad_tiles_;
  static std::vector<Property*> utility_tiles_;
  static std::vector<Property*> street_tiles_;
};
}


#endif //MONOPOLY_BOARD_H
