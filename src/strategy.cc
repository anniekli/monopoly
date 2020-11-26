//
// Created by GWC-CHC-07 on 6/22/2020.
//

#include "strategy.h"

namespace monopoly {
  Player Strategy::GetPlayer() {
    return player_;
  }
  
  void Strategy::PerformAction(Board &board) {
    if (board.GetTileAtPos(player_.GetPosition())->GetGroup() != g_special) {
  
      Property *property = dynamic_cast<Property*> (board.GetTileAtPos
              (player_.GetPosition()));
      
      if (property->GetOwnerId() == -1 && player_.GetMoney() >= property->GetPrice()) {
        property->BuyProperty(player_.GetId());
        player_.AddMoney(0 - property->GetPrice());
        
      } else if (property->GetOwnerId() != player_.GetId()) {
//        if (player_.GetMoney() >= property->GetRent()) {
//          player_.AddMoney(0 - property->GetRent());
//        } else {
//          for (Property *street : board.GetStreets()) {
//
//          }
//        }
      }
    }
  }
}