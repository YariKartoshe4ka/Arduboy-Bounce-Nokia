#pragma once

#include "assets.h"
#include "constants.h"

enum EntityType : uint8_t { ENTITY_EMPTY, ENTITY_BLOCK };

struct Entity {
  EntityType type;
  int16_t x, y;

  uint8_t state;
  const uint8_t *image;

  Entity() = default;
  Entity(int16_t x, int16_t y) : type(ENTITY_EMPTY), x(x), y(y){};

  Rect rect();
};

struct Block : Entity {
  Block(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_BLOCK;
    image = IMAGE_BLOCK;
  };
};

struct Ball {
  float x, y, vel_x, vel_y, ac_x, ac_y;

  uint8_t state;
  const uint8_t *image;

  Ball() = default;
  Ball(int16_t x, int16_t y);

  void check_events();

  void move_hor();
  void collide_hor();

  void move_ver();
  void collide_ver();

  void draw();

  Rect rect();
};
