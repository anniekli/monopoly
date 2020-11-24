//
// Created by GWC-CHC-07 on 7/6/2020.
//

#include "Card/funds.h"

namespace monopoly {
  void Funds::PerformAction(std::vector<Player> &players,
          const std::vector<Tile *> &tiles, int player_id) const {
    
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
      // TODO: add attribute to player object to allow bought properties to
      //  be viewed
    }
  }
}