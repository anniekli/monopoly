//
// Created by GWC-CHC-07 on 6/30/2020.
//

#include "Card/move.h"

namespace monopoly {
  void Move::PerformAction(Player &player, const std::vector<Tile*> &tiles) const {
    if (action_ == CardAction::kMove) {
      player.SetPosition(destination_);
      return;
    
    } else if (action_ == CardAction::kMoveNearest) {
      if (group_ == g_utility) {
        int curr_pos = player.GetPosition() + 1;
        
        for (int i = 0; i < 40; i++) {
          if (tiles.at(curr_pos % 40)->GetGroup() == g_utility) {
            player.SetPosition(curr_pos);
            return;
          
          } else {
            curr_pos++;
          }
        }
      }
      
    } else if (action_ == CardAction::kMoveSpaces) {
      player.UpdatePosition(destination_);
      return;
    }
  }
}