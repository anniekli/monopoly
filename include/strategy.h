//
// Created by GWC-CHC-07 on 6/22/2020.
//

#ifndef MONOPOLY_STRATEGY_H
#define MONOPOLY_STRATEGY_H

#include "board.h"
#include "player.h"

namespace monopoly {
  enum class TurnAction {
    kBuyProperty
  };

class Strategy {

public:
  Strategy(){};
  Strategy(Player player) : player_(player) {};
  
  void PerformAction(Board &board);
  Player GetPlayer();

private:
  Player player_;
};
}

#endif //MONOPOLY_STRATEGY_H
