//
// Created by Shreya Sharma on 4/22/20.
//

#pragma once

#include <mylibrary/gameboard.h>
#include <cinder/Rand.h>

#include "mylibrary/gameboard.h"
#include "../include/mylibrary/gameboard.h"


namespace mylibrary {

    mylibrary::Gameboard::Gameboard() : board{},
    score{0} {}

    void mylibrary::Gameboard::SetBoardSize() {
      board.resize(kBoardSize);
      for (int i = 0; i < board.size(); i++) {
        board[i].resize(kBoardSize);
        for (int j = 0; j < kBoardSize; j++) {
          board[i][j] = Block(0, i, j);
        }
      }
    }

    std::vector<int> mylibrary::Gameboard::GetRandomEmptyPosition() {
      std::vector<int> empty_position;

      for (int i = 0; i < kBoardSize*kBoardSize; i++) {
        int random_row = rand() % (kBoardSize);
        int random_col = rand() % (kBoardSize);
        if (board[random_row][random_col].value == 0) {
          //space is empty and valid
          empty_position.push_back(random_row);
          empty_position.push_back(random_col);
          return empty_position;
        }
      }
      // Return empty vector if no empty spaces on board, game should be over
      return empty_position;
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

    bool Gameboard::AddRandomBlock() {
      std::vector<int> empty_position = GetRandomEmptyPosition();
      if (!empty_position.empty()) {
        board[empty_position[0]][empty_position[1]].SetValue(2);
        return true;
      }
      return false;
    }

    void Gameboard::MoveLeft() {

      for (int col = 0; col < kBoardSize; col++) {
        for (int row = 0; row < kBoardSize; row++) {

          for (int target = row + 1; target < kBoardSize; target++) {

            if (board[target][col].value != 0) {

              if (board[row][col].value == 0) {

                board[row][col].value = board[target][col].value;
                board[target][col].value = 0;

              } else if (board[row][col].value == board[target][col].value) {

                board[row][col].value += board[target][col].value;
                score += board[row][col].value;
                board[target][col].value = 0;

              }
            }
          }
        }
      }

    }

    void Gameboard::MoveUp() {

      for (int row = 0; row < kBoardSize; row++) {
        for (int col = 0; col < kBoardSize; col++) {

          for (int target = col + 1; target < kBoardSize; target++) {

            if (board[row][target].value != 0) {

              if (board[row][col].value == 0) {

                board[row][col].value = board[row][target].value;
                board[row][target].value = 0;

              } else if (board[row][col].value == board[row][target].value) {

                board[row][col].value += board[row][target].value;
                score += board[row][col].value;
                board[row][target].value = 0;

              }
            }
          }
        }
      }

    }
}