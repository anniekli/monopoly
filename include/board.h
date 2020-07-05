//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H

#include "Tile/tile.h"
#include "Tile/property.h"
#include "Card/card.h"
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

namespace monopoly {

extern const std::string g_special;
extern const std::string g_utility;
extern const std::string g_railroad;
extern const std::string g_chance;
extern const std::string g_chest;
extern const std::string g_water;
extern const std::string g_electricity;
extern const std::string g_go_to_jail;


using std::string;
using json = nlohmann::json;

class Board {

public:
  Board(){};
  Board(std::string &filepath);
  
  Tile GetTile();
//  Card GetChanceCard();
//  Card GetChestCard();
  std::vector<Tile*> GetTiles();
  Tile* GetTileAtPos(int position);
  std::vector<Property*> GetStreets() const;
  std::vector<Property*> GetRailroads() const;
  std::vector<Property*> GetUtilities() const;
  int GetJailPosition();
  friend Property;

private:
  
  void PopulateTiles();
  void PopulateChanceCards();
  void PopulateCommunityChestCards();
  
  std::ifstream infile;
  json j;
  std::vector<Tile*> tiles;
  static std::vector<Property*> railroad_tiles_;
  static std::vector<Property*> utility_tiles_;
  static std::vector<Property*> street_tiles_;
  
  std::vector<Card*> chance_cards_;
  std::vector<Card*> community_chest_cards_;
};
}


#endif //MONOPOLY_BOARD_H
