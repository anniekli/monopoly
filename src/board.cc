//
// Created by GWC-CHC-07 on 6/1/2020.
//

#include <cinder/app/AppBase.h>
#include <Card/funds.h>
#include <random>
#include "board.h"
#include "Tile/property.h"
#include "Tile/special.h"
#include "Card/move.h"
#include "Card/card.h"

using json = nlohmann::json;

namespace monopoly {
  std::vector<Property*> Board::railroad_tiles_ = {};
  std::vector<Property*> Board::utility_tiles_ = {};
  std::vector<Property*> Board::street_tiles_ = {};
  
  Board::Board(std::string &filepath) {
    infile.open(cinder::app::getAssetPath(filepath), std::ios::in);
  
    if (infile.good()) {
      infile >> j;
      PopulateTiles();
      PopulateCards("chance", chance_cards_);
      PopulateCards("communitychest", community_chest_cards_);
    }
  }
  
  void Board::PopulateTiles() {
    int index = 0;
  
    // populate tile vector
    for (auto& tile : j["tiles"]) {
      Tile *my_tile;
      
      // if the tile is "Special", create a Special tile
      if (tile["group"] == g_special) {
        my_tile = new Special(tile["name"], index, 0, tile["group"]);
        
      } else {
        // if the tile is not a "Special" type
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
      
          Property *property = dynamic_cast<Property *>(my_tile);
          if (tile["group"] == g_railroad) {
            railroad_tiles_.push_back(property);
          } else {
            utility_tiles_.push_back(property);
          }
      
        } else {
          // if tile is a regular property
          int rgb[3];
          for (int j = 0; j < 3; j++) {
            rgb[j] = tile["rgb"][j];
          }
      
          my_tile = new Property(tile["name"], index,
                                 tile["price"], rent, tile["housecost"],
                                 tile["group"], rgb);
      
          Property *property = dynamic_cast<Property *>(my_tile);
          street_tiles_.push_back(property);
        }
      }
  
      tiles.push_back(my_tile);
      index++;
    }
  }
  
  void Board::PopulateCards(const std::string& card_type, std::vector<Card*>
          card_vec) {
    
    for (const auto& card : j[card_type]) {
      Card *my_card;
      if (card["action"] == "move") {
        my_card = new Move(card["title"], CardAction::kMove,
                           (int) card["destination"]);
    
      } else if (card["action"] == "movenearest") {
        my_card = new Move(card["title"], CardAction::kMoveNearest,
                           card["group"], card["rentmultiplier"]);
    
      } else if (card["action"] == "movespaces") {
        my_card = new Move(card["title"], CardAction::kMoveSpaces,
                           (int) card["count"]);
    
      } else if (card["action"] == "jail") {
        my_card = new Move(card["title"], CardAction::kJail,
                           card["subaction"].get<string>());
    
      } else if (card["action"] == "addfunds") {
        my_card = new Funds(card["title"], CardAction::kAddFunds,
                            card["amount"]);
    
      } else if (card["action"] == "addfundstoplayers") {
        my_card = new Funds(card["title"], CardAction::kAddFundsToPlayers,
                            card["amount"]);
    
      } else if (card["action"] == "propertycharges") {
        my_card = new Funds(card["title"], CardAction::kPropertyCharges,
                            card["house"], card["hotel"]);
      }
      card_vec.push_back(my_card);
    }
  
    // shuffle the vector of cards
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(card_vec.begin(), card_vec.end(), g);
  }
  
  int Board::GetJailPosition() {
    for (auto& tile : tiles) {
      if (tile->GetName() == g_jail) {
        return tile->GetPosition();
      }
    }
    // if jail does not exist, there is an error
    return -1;
  }
  
  Card* Board::DrawChestCard() {
    Card *card = community_chest_cards_.back();
    community_chest_cards_.pop_back();
    return card;
  }
  
  Card * Board::DrawChanceCard() {
    Card *card = chance_cards_.back();
    chance_cards_.pop_back();
    return card;
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