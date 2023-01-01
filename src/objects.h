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
