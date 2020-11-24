//
// Created by GWC-CHC-07 on 6/30/2020.
//

#ifndef MONOPOLY_MOVE_CARD_H
#define MONOPOLY_MOVE_CARD_H


#include "card.h"

namespace monopoly {

class Move : public Card {
public:
  Move(std::string title, CardAction action, int destination)
  : Card{title, action}, destination_{destination} {};
  
  Move(std::string title, CardAction action, std::string subaction)
          : Card{title, action}, subaction_{subaction} {};
  
  Move(std::string title, CardAction action, std::string group, int
  rent_multiplier)
  : Card{title, action},  group_{group}, rent_multiplier_{rent_multiplier} {};
  
  void PerformAction(std::vector<Player> &players,
          const std::vector<Tile *> &tiles, int player_id) const override;
  
private:
  int destination_;
  std::string group_;
  std::string subaction_;
  int rent_multiplier_;
};
}
#endif //MONOPOLY_MOVE_CARD_H
