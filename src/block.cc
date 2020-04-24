//
// Created by Shreya Sharma on 4/22/20.
//

#pragma once

#include "mylibrary/block.h"
#include "../include/mylibrary/block.h"


namespace mylibrary {

mylibrary::Block::Block() : value{0} {}

mylibrary::Block::Block(int set_value_, int set_row, int set_col) {
  value = set_value_;
  row = set_row;
  col = set_col;
}
void Block::SetValue(int set_value) {
  value = set_value;
}
cinder::Color Block::GetColor(int mode_) {
  if (mode_ == 0) {
    if (value == 2048) {return cinder::Color(0.737, 0.956, 0.870);}
    else if (value == 1024) {return cinder::Color(0.803, 0.898, 0.843);}
    else if (value == 512) {return cinder::Color(0.870, 0.839, 0.819);}
    else if (value == 256) {return cinder::Color(0.933, 0.776, 0.792);}
    else if (value == 128) {return cinder::Color(1, 0.717, 0.764);}
    else if (value == 64) {return cinder::Color(0.862, 0.760, 0.882);}
    else if (value == 32) {return cinder::Color(0.949, 0.835, 0.972);}
    else if (value == 16) {return cinder::Color(0.901, 0.752, 0.913);}
    else if (value == 8) {return cinder::Color(0.866, 0.733, 0.886);}
    else if (value == 4) {return cinder::Color(0.827, 0.713, 0.854);}
    else if (value == 2) {return cinder::Color(0.749, 0.670, 0.796);}
  } else if (mode_ == 1) {
    // Temporary, will implement dark mode color scheme later
    return cinder::Color(.5,.5,.5);
  }
}

} //namespace mylibrary