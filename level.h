#pragma once

#include <Arduboy2.h>

struct Level {
  uint8_t level_no,  // Level number
    width,           // Level width in blocks
    height;          // Level height in blocks

  int16_t shift_x,  // Blocks between left level side and surface
    shift_y,        // Blocks between top level sise and surface
    prev_shift_x, prev_shift_y;

  uint8_t right_bound = 0,  // Free bound, if level moves left
    down_bound = 0;         // Free bound, if ball moves down

  void init(uint8_t level_no);
  void move_hor(int16_t hor);
  void load_entity(uint8_t to_i, uint8_t to_j, uint8_t from_i, uint8_t from_j);
};
