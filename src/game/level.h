#pragma once

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "objects.h"

class States {
  struct {
    uint16_t key;
    uint8_t value;
  } table[STATES_TABLE_SIZE];

  uint8_t size;

  uint16_t getKey(Entity *entity);

 public:
  States();

  uint8_t get(Entity *entity);
  void set(Entity *entity, uint8_t state);
};

class Level {
 private:
  Entity entities[SURFACE_B_H][SURFACE_B_W];

  uint8_t level_no,  // Level number
    width,           // Level width in blocks
    height;          // Level height in blocks

  int8_t hor_bound = 0;  // Free bound, if level moves left

  uint8_t *rle;
  uint16_t rle_i;

 public:
  States states;

  /* Meta vars */
  uint8_t endX, endY, rings;

  int16_t offset_x, offset_y,
    shift_x,  // Blocks between left level side and surface
    shift_y;  // Blocks between top level sise and surface

  Level() = default;
  Level(uint8_t level_no);

  void load_entity(uint8_t to_i, uint8_t to_j, uint16_t from_i, uint16_t from_j);
  void update_offsets();
  uint8_t translate_col(uint8_t j);
  uint8_t build_collide_area();
  void move_hor();
  void move_ver();
  void draw_surface();
  void draw_interface();

  uint8_t operator[](uint16_t i);
};

extern Level level;
extern Entity *area[COLLIDE_AREA_SIZE];
