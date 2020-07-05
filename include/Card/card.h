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
    kRemoveFunds,
    kMove,
    kMoveSpaces,
    kMoveNearest
  };

class Card {
public:
  Card(){};
  Card(std::string title, CardAction action);
  std::string GetTitle();
  virtual void PerformAction(Player &player, const std::vector<Tile*> &tiles)
  const {};

protected:
  std::string title_;
  CardAction action_;
  
};
}



#endif //MONOPOLY_CARD_H
