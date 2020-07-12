//
// Created by GWC-CHC-07 on 6/18/2020.
//

#ifndef MONOPOLY_CARD_H
#define MONOPOLY_CARD_H

#include <board.h>
#include "board.h"
#include "player.h"


namespace monopoly {
  enum class CardAction {
    kAddFunds,
    kAddFundsToPlayers,
    kMove,
    kMoveSpaces,
    kMoveNearest
  };

class Card {
public:
  Card(){};
  Card(std::string title, CardAction action);
  std::string GetTitle();
  virtual void PerformAction(std::vector<Player> &players,
                             const std::vector<Tile *> &tiles,
                             int player_id) const {};

protected:
  std::string title_;
  CardAction action_;
  
};
}



#endif //MONOPOLY_CARD_H
