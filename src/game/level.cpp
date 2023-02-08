#include "level.h"

#include <Arduboy2Ex.h>

#include "../assets/images.h"
#include "../assets/levels.h"
#include "../constants.h"
#include "ball.h"
#include "objects.h"
#include "scene.h"

extern Arduboy2Ex arduboy;
extern Sprites sprites;

Level level;
Entity *area[COLLIDE_AREA_SIZE];

States::States() {
  size = 0;
};

uint16_t States::getKey(Entity *entity) {
  return (entity->y / 8 << 8) + entity->x / 8;
};

uint8_t States::get(Entity *entity) {
  uint16_t key = getKey(entity);

  for (uint8_t i = 0; i < size; ++i) {
    if (table[i].key == key) return table[i].value;
  }
  return 0;
};

void States::set(Entity *entity, uint8_t state) {
  uint16_t key = getKey(entity);
  table[size++] = {key, state};
}

Level::Level(uint8_t level_no) {
  this->level_no = level_no;

  states = States();

  shift_x = 0;
  shift_y = -SURFACE_B_H;

  rle_i = 0xffff;

  rings = (*this)[5];
  width = (*this)[6];
  height = (*this)[7];
};

void Level::load_entity(uint8_t to_i, uint8_t to_j, uint16_t from_i, uint16_t from_j) {
  uint8_t entity_byte = (*this)[from_i * width + from_j + 8];

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
      entities[to_i][to_j] = Ramp(from_j * 8, from_i * 8);
      break;
    }
    case 0x10: {
      entities[to_i][to_j] = RingVer(from_j * 8 + 2, from_i * 8);
      break;
    }
    case 0x11: {
      entities[to_i][to_j] = RingHor(from_j * 8, from_i * 8 + 2);
      break;
    }
  }
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
      load_entity(i, hor_bound, shift_y + i, shift_x + SURFACE_B_W - 1);

    ++hor_bound;
    if (hor_bound == SURFACE_B_W) hor_bound = 0;
  }

  // Horizontal scrolling (left for ball)
  if (hor < 0) {
    shift_x += min(0, SURFACE_B_W + hor);
    hor = max(hor, -SURFACE_B_W);
  }
  for (; hor < 0; ++hor) {
    --shift_x;

    --hor_bound;
    if (hor_bound == -1) hor_bound += SURFACE_B_W;

    for (uint8_t i = 0; i < SURFACE_B_H; ++i)
      load_entity(i, hor_bound, shift_y + i, shift_x);
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

  hor_bound = 0;
};

uint8_t Level::translate_col(uint8_t j) {
  uint8_t col = j + hor_bound;
  if (col >= SURFACE_B_W) col -= SURFACE_B_W;
  return col;
};

uint8_t Level::build_collide_area() {
  Rect rect_ball = ball.rect();
  int8_t centerx = (rect_ball.x + rect_ball.width / 2) / 8 - shift_x,
         centery = (rect_ball.y + rect_ball.height / 2) / 8 - shift_y;

  uint8_t collide_area_size = 0;
  for (uint8_t k = max(0, centerx - 1); k <= min(SURFACE_B_W - 1, centerx + 1); ++k) {
    uint8_t j = translate_col(k);
    for (uint8_t i = max(0, centery - 1); i <= min(SURFACE_B_H - 1, centery + 1); ++i) {
      area[collide_area_size] = &entities[i][j];
      ++collide_area_size;
    }
  }

  for (uint8_t i = 1; i < COLLIDE_AREA_SIZE; ++i) {  // Insertion sort
    Entity *tmp = area[i];
    int8_t j = i - 1;
    for (; j >= 0 && area[j]->type > tmp->type; --j) {
      area[j + 1] = area[j];
    }
    area[j + 1] = tmp;
  }
  return collide_area_size;
};

void Level::draw_surface() {
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

void Level::draw_interface() {
  arduboy.setTextColor(WHITE);

  // Draw rings info
  arduboy.setCursor(1, 2);
  arduboy.print(rings);
  arduboy.print(F("x"));
  sprites.drawOverwrite(13, 1, IMAGE_RING_INFO, 0);

  // Draw ball info
  arduboy.setCursor(1, 11);
  arduboy.print(3);
  arduboy.print(F("x"));
  sprites.drawOverwrite(13, 10, IMAGE_BALL_INFO, 0);
};

uint8_t Level::operator[](uint16_t i) {
  if (i < 8) return pgm_read_byte(&LEVELS[level_no][i]);
  if (rle_i > i) {
    rle = (uint8_t *)LEVELS[level_no] + 8;
    rle_i = 8;
  }

  while (rle_i < i) {
    if (pgm_read_byte(rle + 1) == 0xff) {
      uint8_t cnt = pgm_read_byte(rle + 2);
      if (rle_i + cnt > i) break;
      rle += 3;
      rle_i += cnt;
    } else {
      ++rle;
      ++rle_i;
    }
  }

  return pgm_read_byte(rle);
}
