#pragma once

#include "../assets/images.h"

enum EntityType : uint8_t {
  ENTITY_EMPTY,
  ENTITY_RAMP_TL,
  ENTITY_RAMP_TR,
  ENTITY_BLOCK,
  ENTITY_CRYS,
  ENTITY_CRYS_BALL,
  ENTITY_SPIKE_DOWN,
  ENTITY_SPIKE_LEFT,
  ENTITY_SPIKE_UP,
  ENTITY_SPIKE_RIGHT,
  ENTITY_RING_VER,
  ENTITY_RING_HOR,
  ENTITY_BIG_RING_VER,
  ENTITY_BIG_RING_HOR,
  ENTITY_DEFLATOR_DOWN,
  ENTITY_DEFLATOR_LEFT,
  ENTITY_DEFLATOR_UP,
  ENTITY_DEFLATOR_RIGHT,
  ENTITY_INFLATOR_DOWN,
  ENTITY_INFLATOR_LEFT,
  ENTITY_INFLATOR_UP,
  ENTITY_INFLATOR_RIGHT,
  ENTITY_END
};

struct Entity {
  EntityType type;
  int16_t x, y;

  const uint8_t *image;

  Entity() = default;
  Entity(int16_t x, int16_t y) : type(ENTITY_EMPTY), x(x), y(y) {};
  Entity(int16_t x, int16_t y, EntityType type, const uint8_t *image)
      : type(type), x(x), y(y), image(image) {};

  Rect rect();
};

void loadEntity(Entity &entity, uint16_t x, uint16_t y);
