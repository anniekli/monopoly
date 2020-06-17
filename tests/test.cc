// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <player.h>

using namespace monopoly;


TEST_CASE("Test Player class", "[player]") {
  Player player_ = Player();
  REQUIRE(player_.GetPosition() == 0);
  
  SECTION("Test Update Position") {
    player_.UpdatePosition(12);
    REQUIRE(player_.GetPosition() == 12);
  }
  
  SECTION("Update position past 39") {
    player_.UpdatePosition(41);
    REQUIRE(player_.GetPosition() == 1);
  }
}