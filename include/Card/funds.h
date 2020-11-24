//
// Created by GWC-CHC-07 on 7/6/2020.
//

#ifndef MONOPOLY_FUNDS_H
#define MONOPOLY_FUNDS_H

#include <string>
#include "card.h"

namespace monopoly {

class Funds : public Card {
public:
  Funds(std::string title, CardAction action, int amount)
  : Card{title, action}, amount_{amount} {};
  
  Funds(std::string title, CardAction action, int house, int hotel)
  : Card{title, action}, house_charge{house}, hotel_charge{hotel} {};
  
  void PerformAction(std::vector<Player> &players,
          const std::vector<Tile *> &tiles, int player_id) const override;
  
private:
  int amount_;
  int house_charge;
  int hotel_charge;
};
}

#endif //MONOPOLY_FUNDS_H
