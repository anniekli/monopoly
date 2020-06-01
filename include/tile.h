//
// Created by GWC-CHC-07 on 6/1/2020.
//

#ifndef MONOPOLY_TILE_H
#define MONOPOLY_TILE_H

class Tile {
public:
  Tile(){};
  std::string GetName();
  std::string GetGroup();
  int GetPrice();
  
  int GetRent(int num_houses);
  int GetHouseCost();
  int GetPosition();
  
  // find some way to return group type as an object...look into inheritance

};


#endif //MONOPOLY_TILE_H
