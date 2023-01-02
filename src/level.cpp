#include "level.h"

#include <Arduboy2.h>

#include "assets.h"
#include "ball.h"
#include "constants.h"
#include "levels.h"
#include "objects.h"

extern Arduboy2 arduboy;
extern Entity *area[COLLIDE_AREA_SIZE];
extern Sprites sprites;
extern Ball ball;

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
    case 0x02: {
      entities[to_i][to_j] = Stair(from_j * 8, from_i * 8);
      break;
    }
  }
};

Level::Level(uint8_t level_no) {
  this->level_no = level_no;

  shift_x = 0;
  shift_y = -SURFACE_B_H;

  width = pgm_read_byte(&LEVELS[level_no][0]);
  height = pgm_read_byte(&LEVELS[level_no][1]);

  move_ver();
};

void Level::move_hor() {
  update_offsets();

  int16_t next_shift_x = -offset_x / 8;
  int16_t hor = next_shift_x - shift_x;

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

    for (uint8_t i = 0; i < SURFACE_B_H; ++i)
      load_entity(i, right_bound, shift_y + i, shift_x);
  }
};

void Level::update_offsets() {
  int16_t ball_centerx = round(ball.x) + pgm_read_byte(&ball.image[0]) / 2.;

  offset_x = 0;
  if (ball_centerx > SURFACE_W / 2) {
    offset_x = max(SURFACE_W / 2 - ball_centerx, SURFACE_W - width * 8);
  }

  offset_y = -shift_y * 8;
}

void Level::move_ver() {
  int16_t next_shift_y = round(ball.y) / 8 / 7 * 7;
  int16_t ver = next_shift_y - shift_y;

  if (!ver) return;

  // Vertical scrolling (up/down for ball)
  shift_y += ver;

  for (uint8_t i = 0; i < SURFACE_B_H; ++i)
    for (uint8_t j = 0; j < SURFACE_B_W; ++j)
      load_entity(i, j, shift_y + i, shift_x + j);

  right_bound = 0;
};

uint8_t Level::translate_col(uint8_t j) {
  uint8_t col = j + right_bound;
  if (col >= SURFACE_B_W) col -= SURFACE_B_W;
  return col;
};

void Level::build_collide_area() {
  Rect rect_ball = ball.rect();
  int8_t centerx = (rect_ball.x + rect_ball.width / 2) / 8 - shift_x,
         centery = (rect_ball.y + rect_ball.height / 2) / 8 - shift_y;

  uint8_t l = 0;
  for (uint8_t k = max(0, centerx - 1); k <= min(SURFACE_B_W - 1, centerx + 1); ++k) {
    uint8_t j = translate_col(k);
    for (uint8_t i = max(0, centery - 1); i <= min(SURFACE_B_H - 1, centery + 1); ++i) {
      area[l] = &entities[i][j];
      ++l;
    }
  }
  for (; l < COLLIDE_AREA_SIZE; ++l)
    area[l] = &Entity(0, 0);

  for (uint8_t i = 1; i < COLLIDE_AREA_SIZE; ++i) {  // Insertion sort
    Entity *tmp = area[i];
    int8_t j = i - 1;
    for (; j >= 0 && area[j]->type > tmp->type; --j) {
      area[j + 1] = area[j];
    }
    area[j + 1] = tmp;
  }
};

void Level::draw() {
  for (uint8_t k = 0; k < SURFACE_B_W; ++k) {
    uint8_t j = translate_col(k);
    for (uint8_t i = 0; i < SURFACE_B_H; ++i) {
      if (entities[i][j].type != ENTITY_EMPTY) {
        sprites.drawOverwrite(
          offset_x + SURFACE_X + entities[i][j].x, offset_y + entities[i][j].y,
          entities[i][j].image, 0
        );
      }
    }
  }
};
