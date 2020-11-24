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
  
  void PerformAction(const std::vector<Tile*> &tiles, int player_id) const override;


private:
  int amount_;
};

}



#endif //MONOPOLY_FUNDS_H
