#pragma once

#include <Arduboy2.h>

struct Level {
  uint8_t level_no,  // Level number
    width,           // Level width in blocks
    height;          // Level height in blocks

  int16_t offset_x, offset_y,
    shift_x,  // Blocks between left level side and surface
    shift_y;  // Blocks between top level sise and surface

  int16_t right_bound = 0;  // Free bound, if level moves left

  Level() = default;
  Level(uint8_t level_no);

  void load_entity(uint8_t to_i, uint8_t to_j, uint8_t from_i, uint8_t from_j);
  void update_offsets();
  uint8_t translate_col(uint8_t j);
  void move_hor();
  void move_ver();
  void draw();
};
