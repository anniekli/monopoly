//
// Created by GWC-CHC-07 on 6/30/2020.
//

#include "Card/move.h"

namespace monopoly {
  void Move::PerformAction(const std::vector<Tile *> &tiles,
                           int player_id) const {
    
    
    if (action_ == CardAction::kMove) {
      return;
    
    } else if (action_ == CardAction::kMoveNearest) {
      
    } else if (action_ == CardAction::kMoveSpaces) {
      return;
    }
  }
}