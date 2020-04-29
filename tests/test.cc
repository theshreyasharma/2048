// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/database.h>
#include <mylibrary/gameboard.h>
#include <mylibrary/block.h>

#include <catch2/catch.hpp>

TEST_CASE("Gameboard construction and GetRandomEmptyPosition", "[gameboard][get-random-empty-position]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  // Make sure board is empty
  REQUIRE(gameboard.board.size() == 4);
  REQUIRE(gameboard.board[2].size() == 4);
  // Every Block should have value 0
  REQUIRE(gameboard.board[2][2].value == 0);

  SECTION("Test Get Random Empty Position") {
    std::vector<int> empty_pos_ = gameboard.GetRandomEmptyPosition();
    //Empty board should return a vector of size 2 within the boards bounds
    REQUIRE(empty_pos_.size() == 2);
    REQUIRE(empty_pos_[0] <= 3);
    REQUIRE(empty_pos_[1] <= 3);
  }

  SECTION("GetRandomEmptyPosition Shouldn't return a taken spot") {
    gameboard.board[1][2].value = 8;
    std::vector<int> empty_pos_ = gameboard.GetRandomEmptyPosition();
    REQUIRE(empty_pos_[0] != 1);
    REQUIRE(empty_pos_[1] != 2);
  }

  SECTION("If all spots are taken, should return an empty vector") {

    for (auto & i : gameboard.board) {
      for (auto & j : i) {
        j.value = 2;
      }
    }

    std::vector<int> empty_pos_ = gameboard.GetRandomEmptyPosition();
    REQUIRE(empty_pos_.empty());
  }

}


TEST_CASE("Gameboard Add Random Block", "[gameboard][add-random-block]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  SECTION("Add random block to board should always be succesful") {
    bool was_success_ = gameboard.AddRandomBlock();
    REQUIRE(was_success_);
  }

  SECTION("Cannot add block to a full board") {
    for (auto & i : gameboard.board) {
      for (auto & j : i) {
        j.value = 2;
      }
    }

    bool was_success_ = gameboard.AddRandomBlock();
    REQUIRE(!was_success_);
  }

}

TEST_CASE("Gameboard Get Pixel Values", "[gameboard][row-pixel-val][column-pixel-val]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  SECTION("At second row") {
    std::vector<int> pixel_row_2_ = gameboard.GetRowPixelVal(1);
    REQUIRE(pixel_row_2_.size() == 2);
    REQUIRE(pixel_row_2_[0] == 250);
    REQUIRE(pixel_row_2_[1] == 400);
  }

  SECTION("At third column") {
    std::vector<int> pixel_col_3_ = gameboard.GetColumnPixelVal(2);
    REQUIRE(pixel_col_3_.size() == 2);
    REQUIRE(pixel_col_3_[0] == 400);
    REQUIRE(pixel_col_3_[1] == 550);
  }

  SECTION("Invalid Index returns empty vectors") {
    std::vector<int> invalid_row = gameboard.GetRowPixelVal(9);
    std::vector<int> invalid_col = gameboard.GetColumnPixelVal(38);
    REQUIRE(invalid_col.empty());
    REQUIRE(invalid_row.empty());
  }

}

TEST_CASE("Gameboard Movement", "[gameboard][move-up][move-right][move-left][move-down]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  SECTION("Should become 4 after MoveLeft") {
    gameboard.board[0][0].SetValue(2);
    gameboard.board[1][0].SetValue(2);
    gameboard.MoveLeft();
    REQUIRE(gameboard.board[0][0].value == 4);
  }

  SECTION("Should become 4 after MoveRight") {
    gameboard.board[0][0].SetValue(2);
    gameboard.board[1][0].SetValue(2);
    gameboard.MoveRight();
    REQUIRE(gameboard.board[3][0].value == 4);
  }

  SECTION("Shouldn't change after MoveLeft") {
    gameboard.board[0][0].SetValue(2);
    gameboard.board[1][0].SetValue(8);
    gameboard.board[2][0].SetValue(16);
    gameboard.MoveLeft();
    REQUIRE(gameboard.board[0][0].value == 2);
    REQUIRE(gameboard.board[1][0].value == 8);
  }

  SECTION("Should become 8 after MoveDown") {
    gameboard.board[0][0].SetValue(4);
    gameboard.board[0][1].SetValue(4);
    gameboard.MoveDown();
    REQUIRE(gameboard.board[0][3].value == 8);
  }

  SECTION("Should become 4 after MoveUp") {
    gameboard.board[0][0].SetValue(8);
    gameboard.board[0][1].SetValue(8);
    gameboard.MoveUp();
    REQUIRE(gameboard.board[0][0].value == 16);
  }

  SECTION("Shouldn't change after MoveUp") {
    gameboard.board[0][0].SetValue(2);
    gameboard.board[0][1].SetValue(8);
    gameboard.board[0][2].SetValue(16);
    gameboard.MoveUp();
    REQUIRE(gameboard.board[0][0].value == 2);
    REQUIRE(gameboard.board[0][1].value == 8);
  }

}

TEST_CASE("Gameboard Contains 2048 Tile", "[gameboard][contains-2048-tile]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  SECTION("Random Block Added won't be 2048 block") {
    gameboard.AddRandomBlock();
    REQUIRE(!gameboard.Contains2048Tile());
  }

  SECTION("Finds Random block successfully") {
    gameboard.board[2][3].value = 2048;
    REQUIRE(gameboard.Contains2048Tile());
  }
}

TEST_CASE("Block methods and constructor", "[block]") {
  mylibrary::Gameboard gameboard;
  gameboard.SetBoardSize();

  SECTION("Can manually set block in gameboard") {
    mylibrary::Block block(2048, 1, 1);
    gameboard.board[1][1] = block;
    REQUIRE(gameboard.board[1][1].value == 2048);
  }

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