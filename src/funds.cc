//
// Created by GWC-CHC-07 on 7/6/2020.
//

#include <Tile/property.h>
#include "Card/funds.h"

namespace monopoly {
  void Funds::PerformAction(std::vector<Player> &players,
          const std::vector<Tile *> &tiles, int player_id, size_t die_one,
          size_t die_two) const {
    
    Player curr_player;
    for (Player &player : players) {
      if (player.GetId() == player_id) {
        curr_player = player;
        break;
      }
    }
  
    if (action_ == CardAction::kAddFunds) {
      curr_player.AddMoney(amount_);
      
    } else if (action_ == CardAction::kAddFundsToPlayers) {
      for (Player player : players) {
        if (player.GetId() != player_id) {
          player.AddMoney(amount_);
        
        } else {
          player.AddMoney(0 - ((players.size() - 1) * amount_));
        }
      }
      
    } else if (action_ == CardAction::kPropertyCharges) {
      for (auto &tile : tiles) {
        if (tile->GetGroup() != "Special") {
          Property* property = dynamic_cast<Property*>(tile);
          if (property->GetOwnerId() == player_id
            && property->GetNumHotels() != -1) {
            curr_player.AddMoney(- (property->GetNumHotels() * hotel_charge));
          } else if (property->GetOwnerId() == player_id
            && property->GetNumHouses() != -1) {
            curr_player.AddMoney(- (property->GetNumHouses() * house_charge));
          }
        }
      }
    }
  }
}