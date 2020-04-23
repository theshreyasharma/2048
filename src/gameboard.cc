//
// Created by Shreya Sharma on 4/22/20.
//

#pragma once

#include <mylibrary/gameboard.h>

#include "mylibrary/gameboard.h"
#include "../include/mylibrary/gameboard.h"


namespace mylibrary {

    mylibrary::Gameboard::Gameboard() : board{} {}

    void mylibrary::Gameboard::SetBoardSize() {
      board.resize(kBoardSize);
      for (int i = 0; i < board.size(); i++) {
        board[i].resize(kBoardSize);
        for (int j = 0; j < kBoardSize; j++) {
          board[i][j] = Block(0, i, j);
        }
      }
    }

    void mylibrary::Gameboard::GetRandomEmptyPosition() {

    }
    std::vector<int> Gameboard::GetRowPixelVal(int row_) const {
      int row_counter = 0;
      std::vector<int> x_values_;
      for (int i = 100; i < 700; i+=150) {
        if (row_counter == row_ || row_counter == row_ + 1) {
          x_values_.push_back(i);
        }
        row_counter++;
      }
      if (row_ == 3) {
        x_values_.push_back(700);
      }
      return x_values_;
    }

    std::vector<int> Gameboard::GetColumnPixelVal(int col_) const {
      int col_counter = 0;
      std::vector<int> y_values_;
      for (int i = 100; i < 700; i+=150) {
        if (col_counter == col_ || col_counter == col_ + 1) {
          y_values_.push_back(i);
        }
        col_counter++;
      }
      if (col_ == 3) {
        y_values_.push_back(700);
      }
      return y_values_;
    }

    }