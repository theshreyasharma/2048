// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/database.h>
#include <mylibrary/gameboard.h>
#include <mylibrary/block.h>

#include <catch2/catch.hpp>

TEST_CASE("Gameboard", "[gameboard]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  // Make sure board is empty
  REQUIRE(gameboard.board.size() == 4);
  REQUIRE(gameboard.board[2].size() == 4);
  REQUIRE(gameboard.board[2][2].value == 0);

}

TEST_CASE("Block", "[block]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  SECTION("SetValue function") {
    gameboard.board[2][2].SetValue(16);
    REQUIRE(gameboard.board[2][2].value == 16);
    gameboard.board[1][2].SetValue(2);
    REQUIRE(gameboard.board[1][2].value == 2);
  }

  SECTION("GetColor function in light mode") {
    gameboard.board[2][2].SetValue(16);
    gameboard.board[1][2].SetValue(2);
    REQUIRE(gameboard.board[1][2].GetColor(0) == cinder::Color(0.749, 0.670, 0.796));
  }
}