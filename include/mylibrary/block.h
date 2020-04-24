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
    cinder::Color GetColor(int mode_);
    void SetValue(int set_value);
    int value;

   private:
    int row;
    int col;
  };
}


#endif  // FINALPROJECT_BLOCK_H
