//
// Created by Shreya Sharma on 4/22/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

#include <cinder/Color.h>
namespace mylibrary {
  class Block {
   public:
    Block();
    Block(int set_value_, int set_row, int set_col);
    /**
     * Returns Color for the block based on color mode and value
     * @param mode_ - light or dark mode
     * @return - Color object
     */
    cinder::Color GetColor(int mode_);
    void SetValue(int set_value);
    /**
     * Value of the block, 2 to some power
     */
    int value;

   private:
    /**
     * Row that block resides in
     */
    int row;
    /**
     * Column that the block resides in
     */
    int col;
  };
}


#endif  // FINALPROJECT_BLOCK_H
