#include "objects.h"

#include <Arduboy2Ex.h>

#include "level.h"

Rect Entity::rect() {
  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};

RingVer::RingVer(int16_t x, int16_t y) : Entity(x, y) {
  type = ENTITY_RING_VER;
  image = (level.states.get(this) ? IMAGE_RING_VER_ACT : IMAGE_RING_VER);
};

RingHor::RingHor(int16_t x, int16_t y) : Entity(x, y) {
  type = ENTITY_RING_HOR;
  image = (level.states.get(this) ? IMAGE_RING_HOR_ACT : IMAGE_RING_HOR);
};

Rect RingHor::rect() {
  return Rect(x, y + 2, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]) - 4);
}
