//
// Created by GWC-CHC-07 on 7/6/2020.
//

#include "Card/funds.h"

namespace monopoly {
  void Funds::PerformAction(std::vector<Player> &players,
                            const std::vector<Tile *> &tiles,
                            int player_id) const {
    
    if (action_ == CardAction::kAddFunds) {
      for (Player player : players) {
        if (player.GetId() == player_id) {
          player.AddMoney(amount_);
        }
      }
      
    } else if (action_ == CardAction::kAddFundsToPlayers) {
      for (Player player : players) {
        if (player.GetId() != player_id) {
          player.AddMoney(amount_);
        
        } else {
          player.AddMoney(0 - ((players.size() - 1) * amount_));
        }
      }
    }
    
  }
}