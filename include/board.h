//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H

#include "Tile/tile.h"
#include "Tile/property.h"
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include "Card/card.h"

namespace monopoly {

extern const std::string g_special;
extern const std::string g_utility;
extern const std::string g_railroad;
extern const std::string g_chance;
extern const std::string g_chest;
extern const std::string g_water;
extern const std::string g_electricity;
extern const std::string g_go_to_jail;
extern const std::string g_jail;

using std::string;
using json = nlohmann::json;

class Board {

public:
  Board(){};
  Board(std::string &filepath);
  
  
  /**
   * Draws the tiles on the screen.
   */
  void DrawTiles() const;
  
  /**
   * Draws (as in picks) the next Chance card from the top of the deck and
   * puts it at the bottom (per official rules) unless it is a "Get Out of
   * Jail Free" card. Then, it is not replaced until the card is used.
   * @return Chance card that was drawn. Return NULL if deck is empty.
   */
  Card* DrawChanceCard();
  
  /**
   * Draws (as in picks) the next Community Chest card from the top of the deck and
   * puts it at the bottom (per official rules) unless it is a "Get Out of
   * Jail Free" card. Then, it is not replaced until the card is used.
   * @return Community Chest card that was drawn. Return NULL if deck is empty.
   */
  Card* DrawChestCard();
  
  const std::vector<Tile*>& GetTiles() const;
  
  /**
   * Gets the Tile object at a certain position on the board. The object can
   * be modified in order to allow the user to purchase the property, buy
   * houses, etc.
   * @param position The position of the tile on the board
   * @return A non-const pointer to the Tile object
   */
  Tile* GetTileAtPos(int position) const;
  
  /**
   * Replaces the "Get Out Of Jail" card to the back of the Chance deck after
   * it is used.
   */
  void ReplaceChanceGetOutJail();
  
  /**
   * Replaces the "Get Out Of Jail" card to the back of the Community Chest
   * deck after it is used.
   */
  void ReplaceChestGetOutJail();
  const std::vector<Property*>& GetStreets() const;
  const std::vector<Property*>& GetRailroads() const;
  const std::vector<Property*>& GetUtilities() const;
  int GetJailPosition() const;
  friend Property;

private:
  
  /**
   * Creates Tile objects from the json and populates the vector of Tiles with
   * the Tile objects
   */
  void PopulateTiles();
  
  /**
   * Creates Card objects from the json and populates the vector of cards
   * with the Card objects, then shuffles the cards so they can be used
   * @param card_type String representing card type in the json file
   * @param card_vec Vector that Card objects should be added to
   */
  void PopulateCards(const std::string& card_type, std::vector<Card*>& card_vec);
  
  std::ifstream infile;
  json j;
  std::vector<Tile*> tiles;
  static std::vector<Property*> railroad_tiles_;
  static std::vector<Property*> utility_tiles_;
  static std::vector<Property*> street_tiles_;
  
  std::vector<Card*> chance_cards_;
  std::vector<Card*> community_chest_cards_;
  
  // store "Get Out Of Jail Free" cards because when they are drawn, they
  // don't get added back until they are used.
  Card* get_out_jail_chest_card_;
  Card* get_out_jail_chance_card_;
};
}

#endif //MONOPOLY_BOARD_H
