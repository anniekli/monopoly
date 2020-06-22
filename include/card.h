//
// Created by GWC-CHC-07 on 6/18/2020.
//

#ifndef MONOPOLY_CARD_H
#define MONOPOLY_CARD_H

namespace monopoly {

class Card {
public:
  Card(){};
  virtual std::string GetTitle() = 0;
  
  
};
}



#endif //MONOPOLY_CARD_H
