//
// Created by Shreya Sharma on 4/22/20.
//

#pragma once

#include <cinder/Rand.h>

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
        // Randomize the empty spot
        int random_row = rand() % (kBoardSize);
        int random_col = rand() % (kBoardSize);
        if (board[random_row][random_col].value == 0) {
          // Space is empty and valid, so add to vector
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

      // Starting at 100, increment by 150 to get 4x150
      for (int i = 100; i <= 700; i+=150) {

        // Have to add beginning and ending values to vector
        if (row_counter == row_ || row_counter == row_ + 1) {
          x_values_.push_back(i);
        }

        row_counter++;

      }
      return x_values_;
    }

    std::vector<int> Gameboard::GetColumnPixelVal(int col_) const {
      int col_counter = 0;
      std::vector<int> y_values_;

      // Starting at 100, increment by 150 to get 4x150
      for (int i = 100; i <= 700; i+=150) {

        // Have to add beginning and ending values to vector
        if (col_counter == col_ || col_counter == col_ + 1) {
          y_values_.push_back(i);
        }

        col_counter++;

      }
      return y_values_;
    }

    bool Gameboard::AddRandomBlock() {
      std::vector<int> empty_position = GetRandomEmptyPosition();

      if (!empty_position.empty()) {
        // Block added should always have value 2
        board[empty_position[0]][empty_position[1]].SetValue(2);
        return true;
      }

      // If there is no empty position, adding block was unsuccessful
      return false;
    }

    void Gameboard::MoveLeft() {

      // Go through each position of the board
      for (int col = 0; col < kBoardSize; col++) {
        for (int row = 0; row < kBoardSize; row++) {

          // Then go through each row from current row to the end of the board
          for (int target = row + 1; target < kBoardSize; target++) {

            if (board[target][col].value != 0) {

              if (board[row][col].value == 0) {
                // Shift blocks into empty rows
                board[row][col].value = board[target][col].value;
                board[target][col].value = 0;

              } else if (board[row][col].value == board[target][col].value) {

                // If two adjacent blocks have same value, combine them
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

      // Go through each position of the board
      for (int row = 0; row < kBoardSize; row++) {
        for (int col = 0; col < kBoardSize; col++) {

          // Then go through each column from current to the end of the board
          for (int target = col + 1; target < kBoardSize; target++) {

            if (board[row][target].value != 0) {

              if (board[row][col].value == 0) {
                // Shift blocks into empty columns
                board[row][col].value = board[row][target].value;
                board[row][target].value = 0;

              } else if (board[row][col].value == board[row][target].value) {
                // If two adjacent blocks have same value, combine them
                board[row][col].value += board[row][target].value;
                score += board[row][col].value;
                board[row][target].value = 0;

              }
            }
          }
        }
      }

    }

    void Gameboard::MoveRight() {

      // Go through each position of the board backwards
      for (int col = kBoardSize - 1; col >= 0; col--) {
        for (int row = kBoardSize - 1; row >= 0; row--) {

          // Then go through each row from current row to the beginning of the board
          for (int target = row - 1; target >= 0; target--) {

            if (board[target][col].value != 0 && target < row) {

              if (board[row][col].value == 0) {

                // Shift blocks into empty rows
                board[row][col].value = board[target][col].value;
                board[target][col].value = 0;

              } else if (board[row][col].value == board[target][col].value) {

                // If two adjacent blocks have same value, combine them
                board[row][col].value += board[target][col].value;
                score += board[row][col].value;
                board[target][col].value = 0;

              }
            }
          }
        }
      }

    }

    void Gameboard::MoveDown() {

      // Go through each position of the board backwards
      for (int row = kBoardSize - 1; row >= 0; row--) {
        for (int col = kBoardSize - 1; col >= 0; col--) {

          // Then go through each column from current column to the beginning of the board
          for (int target = col - 1; target >= 0; target--) {

            if (board[row][target].value != 0 && target < col) {

              if (board[row][col].value == 0) {
                // Shift blocks into empty columns
                board[row][col].value = board[row][target].value;
                board[row][target].value = 0;

              } else if (board[row][col].value == board[row][target].value) {

                // If two adjacent blocks have same value, combine them
                board[row][col].value += board[row][target].value;
                score += board[row][col].value;
                board[row][target].value = 0;

              }
            }
          }
        }
      }

    }

    bool Gameboard::Contains2048Tile() {

      for (int i = 0; i < kBoardSize; i++) {
        for (int j = 0; j < kBoardSize; j++) {

          if (board[i][j].value == 2048) {
            return true;
          }

        }
      }

      return false;
    }

    bool Gameboard::operator==(const Gameboard& other) const {
      if (board.size() != other.board.size()) {
        return false;
      }

      // Check whether all blocks have the same value
      for (int i = 0; i < kBoardSize; i++) {
        for (int j = 0; j < kBoardSize; j++) {
          if (board[i][j].value != other.board[i][j].value) {
            return false;
          }
        }
      }

      return true;

    }

    }