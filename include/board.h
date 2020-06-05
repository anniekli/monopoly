//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H

#include "tile.h"
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

namespace monopoly {

using std::string;
using json = nlohmann::json;

class Board {

public:
  Board(){};
  Board(std::string &filepath);
  
  Tile GetTile();
  void GetChanceCard();
  std::vector<Tile> GetTiles();

private:
  std::ifstream infile;
  json j;
  std::vector<Tile> tiles;
};
}


#endif //MONOPOLY_BOARD_H
