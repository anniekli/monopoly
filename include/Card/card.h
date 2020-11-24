//
// Created by GWC-CHC-07 on 6/18/2020.
//

#ifndef MONOPOLY_CARD_H
#define MONOPOLY_CARD_H
#include <string>
#include <vector>
#include <Tile/tile.h>
#include <player.h>

namespace monopoly {
  enum class CardAction {
    kAddFunds, // add funds to current player
    kAddFundsToPlayers, // add funds to all other players
    kPropertyCharges, // property charges on current player
    kMove, // move to destination
    kMoveSpaces, // move number spaces
    kMoveNearest, // move to nearest tile
    kJail // go to or get out of jail
  };

class Card {
public:
  Card(){};
  Card(std::string title, CardAction action)
  : title_(title), action_(action){};
  std::string GetTitle();
  virtual void PerformAction(std::vector<Player> &players,
                             const std::vector<Tile *> &tiles,
                             int player_id) const {};

protected:
  std::string title_;
  CardAction action_;
  const size_t num_tiles_ = 40;
  
};
}



#endif //MONOPOLY_CARD_H
