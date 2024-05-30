#pragma once

#include "../assets/images.h"

enum EntityType : uint8_t {
  ENTITY_EMPTY,
  ENTITY_RAMP_TL,
  ENTITY_RAMP_TR,
  ENTITY_BLOCK,
  ENTITY_CRYS,
  ENTITY_CRYS_BALL,
  ENTITY_SPIKE,
  ENTITY_RING_VER,
  ENTITY_RING_HOR,
  ENTITY_BIG_RING_VER,
  ENTITY_BIG_RING_HOR,
  ENTITY_DEFLATOR,
  ENTITY_INFLATOR,
  ENTITY_END
};

struct Entity {
  EntityType type;
  int16_t x, y;

  const uint8_t *image;

  Entity() = default;
  Entity(int16_t x, int16_t y) : type(ENTITY_EMPTY), x(x), y(y) {};

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

struct RingHor : Entity {
  RingHor(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RING_HOR;
    image = IMAGE_RING_HOR;
  }
};

struct BigRingVer : Entity {
  BigRingVer(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_BIG_RING_VER;
    image = IMAGE_BIG_RING_VER;
  }
};

struct BigRingHor : Entity {
  BigRingHor(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_BIG_RING_HOR;
    image = IMAGE_BIG_RING_HOR;
  }
};

struct Crys : Entity {
  Crys(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_CRYS;
    image = IMAGE_CRYS;
  }
};

struct CrysBall : Entity {
  CrysBall(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_CRYS_BALL;
    image = IMAGE_CRYS_BALL;
  }
};

struct Spike : Entity {
  Spike(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_SPIKE;
    image = IMAGE_SPIKE;
  }
};

struct Deflator : Entity {
  Deflator(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_DEFLATOR;
    image = IMAGE_DEFLATOR;
  }
};

struct Inflator : Entity {
  Inflator(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_INFLATOR;
    image = IMAGE_INFLATOR;
  }
};

struct RampTL : Entity {
  RampTL(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RAMP_TL;
    image = IMAGE_RAMP_TL;
  }
};

struct RampTR : Entity {
  RampTR(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_RAMP_TR;
    image = IMAGE_RAMP_TR;
  }
};

struct End : Entity {
  End(int16_t x, int16_t y) : Entity(x, y) {
    type = ENTITY_END;
    image = IMAGE_END;
  }
};
