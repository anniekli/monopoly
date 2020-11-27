//
// Created by GWC-CHC-07 on 6/2/2020.
//

#ifndef MONOPOLY_PROPERTY_H
#define MONOPOLY_PROPERTY_H

#include <cinder/Color.h>
#include <cinder/Rect.h>
#include "tile.h"

namespace monopoly {

using cinder::Color;

class Property: public Tile {
public:
  Property(std::string name, int position, int price, int rent[], int
  building_cost, std::string group, int rgb[])
          : Tile{name, position, price, group}, building_cost_(building_cost),
            num_houses_{0} {
    
    // manually copy in the arrays
    for (int i = 0; i < sizeof(rent); i++) {
      rent_[i] = rent[i];
      
      if (i < 3) {
        rgb_[i] = rgb[i];
      }
    }
  }
  
  /**
   * Gets the Rectf object representing the position of the tile
   * @return Rectf of the position of the tile
   */
  cinder::Rectf GetRectf() const override;
  
  /**
   * Gets the vec2 object representing the size of the tile
   * @return vec2 of the tile size
   */
  cinder::ivec2 GetTileVec() const override;
  
  /**
   * Gets the rent of the property based on number of that group owned,
   * number of buildngs (for streets), and/or number on the dice (for utilities)
   * @param die_one The value of the first die
   * @param die_two The value of the second die
   * @return Rent on the property
   */
  int GetRent(size_t die_one, size_t die_two) const;
  
  /**
   * Gets the cost of one house/hotel (the cost of a hotel is the same as a
   * house)
   * @return The cost of one building. Returns 0 if on a property where houses
   * cannot be bought (railroads and utilities)
   */
  size_t GetBuildingCost() const;
  
  /**
   * Allows a house to be purchased if possible
   * @return If the house was able to be purchased
   */
  bool BuyHouse();
  
  /**
   * Allows a hotel to be purchased if there are 4 houses on the property. It
   * automatically trades all the houses for one hotel.
   * @return If the hotel was able to be purchased
   */
  bool BuyHotel();
  int GetNumHouses() const;
  int GetNumHotels() const;
  
  /**
   * Gets the color of the property (applicable for street tiles only; can be
   * called on other tiles but the color returned will be black)
   * @return Color object representing the color of the property to put at
   * the top of the tile. Return type CANNOT be const reference!
   */
  Color GetColor() const;
  
  /**
   * Allows a player to purchase this property
   * @param owner_id The id of the player who bought the property
   */
  void BuyProperty(int owner_id);
  
  /**
   * Gets the id of the owner
   * @return the owner's id. Returns -1 if there is no owner.
   */
  int GetOwnerId();

private:
  int rent_[6];
  int rgb_[3];
  const size_t building_cost_;
  const int mortgage_ = price_ / 2;
  const size_t max_num_houses_ = 4;
  
  size_t num_houses_;
  size_t num_hotels_;
  int owner_ = -1;
  size_t die_one;
  size_t die_two;
  
};
}
#endif //MONOPOLY_PROPERTY_H
