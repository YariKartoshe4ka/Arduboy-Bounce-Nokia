#pragma once

#include "../assets/images.h"

enum EntityType : uint8_t {
  ENTITY_EMPTY,
  ENTITY_RAMP,
  ENTITY_BLOCK,
  ENTITY_CRYS,
  ENTITY_SPIKE,
  ENTITY_RING_VER,
  ENTITY_RING_HOR,
  ENTITY_END
};

struct Entity {
  EntityType type;
  int16_t x, y;

  const uint8_t *image;

  Entity() = default;
  Entity(int16_t x, int16_t y) : type(ENTITY_EMPTY), x(x), y(y){};

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
  };
};

struct RingHor : Entity {
  RingHor(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RING_HOR;
    image = IMAGE_RING_HOR;
  };
};

struct Crys : Entity {
  Crys(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_CRYS;
    image = IMAGE_CRYS;
  }
};

struct Spike : Entity {
  Spike(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_SPIKE;
    image = IMAGE_SPIKE;
  }
};

struct Ramp : Entity {
  Ramp(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RAMP;
    image = IMAGE_RAMP;
  }
};

struct End : Entity {
  End(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_END;
    image = IMAGE_END;
  }
};
