//
// Created by Shreya Sharma on 4/22/20.
//

#ifndef FINALPROJECT_GAMEBOARD_H
#define FINALPROJECT_GAMEBOARD_H

#include <mylibrary/block.h>
#include <string>
#include <vector>

namespace mylibrary {

  class Gameboard{

   public:
    Gameboard();
    bool AddRandomBlock();

    // All the movement ones, return score to add to player score
    int MoveUp();
    int MoveLeft();
    int MoveRight();
    int MoveDown();

    void StartGame();
    std::vector<int> GetRandomEmptyPosition();
    std::vector<int> GetRowPixelVal(int row_) const;
    std::vector<int> GetColumnPixelVal(int col_) const;
    /**
     * Set the size of the board to kBoardSize and fill it with blocks with value 0
     */
    void SetBoardSize();
    const int kBoardSize = 4;
    std::vector<std::vector<mylibrary::Block>> board;
  };


}

#endif  // FINALPROJECT_GAMEBOARD_H
