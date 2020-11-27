//
// Created by GWC-CHC-07 on 6/30/2020.
//

#include <board.h>
#include "Card/move.h"

namespace monopoly {
  void Move::PerformAction(std::vector<Player> &players,
          const std::vector<Tile *> &tiles, int player_id, size_t die_one,
          size_t die_two) const {
    Player player;
    for (Player user : players) {
      if (user.GetId() == player_id) {
        player = user;
      }
    }
  
    if (action_ == CardAction::kMove) {
      player.SetPosition(destination_);
      return;
    
    } else if (action_ == CardAction::kMoveNearest) {
      int curr_pos = player.GetPosition() + 1;
      // this loop simulates going around the board once
      for (size_t i = 0; i < num_tiles_; i++) {
        if (tiles.at(curr_pos % num_tiles_)->GetGroup() == group_) {
          player.SetPosition(curr_pos);

          // Implement the rent-multiplier aspect of the card
          Property* property = dynamic_cast<Property*>(tiles.at
                  (curr_pos));
          if (property->GetOwnerId() != -1 && property->GetOwnerId() !=
          player_id) {
            player.AddMoney(- (property->GetRent(die_one, die_two) *
            rent_multiplier_));
          
          } else {
            // TODO: allow player to purchase the property(likely from
            //  elsewhere in the code)
          }
  
        } else {
          curr_pos++;
        }
      }
      return;
      
    } else if (action_ == CardAction::kMoveSpaces) {
      player.UpdatePosition(destination_);
      return;
      
    } else if (action_ == CardAction::kJail) {
      if (subaction_ == "goto") {
        for (Tile *tile : tiles) {
          if (tile->GetName() == g_jail) {
            player.SetPosition(tile->GetPosition());
            player.SetIsJailed(true);
            return;
          }
        }
      } else {
        player.AddGetOutJailCard();
        return;
      }
    }
  }
}