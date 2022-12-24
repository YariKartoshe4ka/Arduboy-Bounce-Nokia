#include "level.h"

#include <Arduboy2.h>

#include "assets.h"
#include "objects.h"

extern Entity entities[SURFACE_B_H][SURFACE_B_W];
extern Arduboy2 arduboy;

void Level::init(uint8_t level_no) {
  this->level_no = level_no;

  shift_x = shift_y = -1;

  width = pgm_read_byte(&LEVELS[level_no][0]);
  height = pgm_read_byte(&LEVELS[level_no][1]);

  move_hor(SURFACE_B_W);
  shift_x = shift_y = 0;
};

void Level::move_hor(int16_t hor) {
  // Horizontal scrolling (right for ball)
  if (hor > 0) {
    shift_x += min(0, SURFACE_B_W - hor);
    hor = min(hor, SURFACE_B_W);
  }
  for (; hor > 0; --hor) {
    ++shift_x;

    for (uint8_t i = 0; i < SURFACE_B_H; ++i)
      load_entity(i, right_bound, shift_y + i, shift_x + SURFACE_B_W - 1);

    ++right_bound;
    if (right_bound == SURFACE_B_W) right_bound = 0;
  }

  // Horizontal scrolling (left for ball)
  if (hor < 0) {
    shift_x += min(0, SURFACE_B_W + hor);
    hor = max(hor, -SURFACE_B_W);
  }
  for (; hor < 0; ++hor) {
    --shift_x;

    --right_bound;
    if (right_bound == -1) right_bound += SURFACE_B_W;

    for (uint8_t i = 0; i < SURFACE_B_H; ++i) load_entity(i, right_bound, shift_y + i, shift_x);
  }
};

void Level::load_entity(uint8_t to_i, uint8_t to_j, uint8_t from_i, uint8_t from_j) {
  uint8_t entity_byte = pgm_read_byte(&LEVELS[level_no][from_i * width + from_j + 2]);

  switch (entity_byte) {
    case 0x00: {
      entities[to_i][to_j] = Entity(0, 0);
      break;
    }
    case 0x01: {
      entities[to_i][to_j] = Block(from_j * 8, from_i * 8);
      break;
    }
  }
};
