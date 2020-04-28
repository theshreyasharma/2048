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

    /**
     * Default height and width of a 2048 board is 4 high by 4 wide
     */
    const int kBoardSize = 4;

    /**
     * Player score, updated as moves are made
     */
    int score;

    /**
     * Called based on the button the user clicks, slides all the tiles and combines them
     * as the game calls for
     */
    void MoveUp();
    void MoveRight();
    void MoveLeft();
    void MoveDown();

    /**
     * Searches board for a 2048 tile
     * @return true if 2048 block is found, false otherwise
     */
    bool Contains2048Tile();

    /**
     * Operator overload to compare 2 gameboards
     * @param other - Gameboard object to compare to
     * @return true if all values are the same for both, false otherwise
     */
    bool operator==(const Gameboard& other) const;

    /**
     * Adds a block in a random location
     * @return true if adding block was successful, false otherwise
     */
    bool AddRandomBlock();

    /**
     * Finds a random empty tile and returns the coordinates
     * @return vector of ints, x in first position, y in second position
     */
    std::vector<int> GetRandomEmptyPosition();

    /**
     * Associates row with a certain pixel value for drawing
     * @param row_ - row in the array
     * @return - a vector of ints, beginning pixel in the first index, ending pixel in the second index
     */
    std::vector<int> GetRowPixelVal(int row_) const;

    /**
     * Associates row with a certain pixel value for drawing
     * @param col_ - column in the array
     * @return - a vector of ints, beginning pixel in the first index, ending pixel in the second index
     */
    std::vector<int> GetColumnPixelVal(int col_) const;
    /**
     * Set the size of the board to kBoardSize and fill it with blocks with value 0
     */
    void SetBoardSize();

    /**
     * Board object, 2d vector of blocks
     */
    std::vector<std::vector<mylibrary::Block>> board;
  };


}

#endif  // FINALPROJECT_GAMEBOARD_H
