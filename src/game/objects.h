#pragma once

#include "../assets/images.h"

enum EntityType : uint8_t { ENTITY_EMPTY, ENTITY_RAMP, ENTITY_BLOCK, ENTITY_RING_VER };

struct Entity {
  EntityType type;
  int16_t x, y;

  uint8_t state;
  const uint8_t *image;

  Entity() = default;
  Entity(int16_t x, int16_t y) : type(ENTITY_EMPTY), x(x), y(y), state(0){};

  Rect rect();
};

struct Block : Entity {
  Block(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_BLOCK;
    image = IMAGE_BLOCK;
  }
};

struct RingVer : Entity {
  RingVer(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RING_VER;
    image = IMAGE_RING_VER;
  }
};

struct Ramp : Entity {
  Ramp(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RAMP;
    image = IMAGE_RAMP;
  }
};
