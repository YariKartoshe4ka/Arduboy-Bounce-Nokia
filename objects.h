#pragma once

#include "assets.h"
#include "constants.h"


enum EntityType : uint8_t {
  ENTITY_EMPTY, ENTITY_BLOCK
};


#define RECT_ENTITY(e) Rect(e.x, e.y, pgm_read_byte(&e.image[0]), pgm_read_byte(&e.image[1]))


struct Entity {
  EntityType type;
  int16_t x, y;

  uint8_t state;

  const uint8_t *image;

  Entity();
  Entity(int16_t x, int16_t y);
};


struct Block : Entity {
  Block(int16_t x, int16_t y);
};


struct Ball {
  float x, y, vel_x, vel_y, ac_x, ac_y;

  uint8_t state;
  const uint8_t *image;

  Ball();
  Ball(int16_t x, int16_t y);
  void check_events();
  void update();

  float centerx();
};
