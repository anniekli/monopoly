//
// Created by GWC-CHC-07 on 6/18/2020.
//

#ifndef MONOPOLY_CARD_H
#define MONOPOLY_CARD_H
#include <string>
#include <vector>
#include <Tile/tile.h>
#include <player.h>
#include <cinder/Color.h>

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
  Card(std::string title, std::string type, CardAction action)
  : title_(title), type_(type), action_(action){};
  
  const std::string& GetTitle() const;
  const std::string& GetType() const;
  
  /**
   * Gets the color of the card based on its type (orange-red for chance cards,
   * yellow for community chest cards)
   * @return Color object representing the color. This CANNOT be a const
   * reference!
   */
  cinder::Color GetColor() const;
  
  /**
   * Performs the action described on the card
   * @param players Vector of all the players in the game
   * @param tiles
   * @param player_id
   */
  virtual void PerformAction(std::vector<Player> &players,
                             const std::vector<Tile *> &tiles,
                             int player_id) const {};

protected:
  std::string title_;
  std::string type_;
  CardAction action_;
  const size_t num_tiles_ = 40;
  
};
}



#endif //MONOPOLY_CARD_H
