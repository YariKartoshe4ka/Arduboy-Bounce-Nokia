#include "objects.h"

#include <Arduboy2.h>

#include "level.h"

void loadEntity(Entity &entity, uint16_t x, uint16_t y) {
  uint8_t entityByte = level[8 + y * level.width + x];

  x *= 8;
  y *= 8;

#define ADD_ENTITY(code, name, x, y)                    \
  case (code): {                                        \
    entity = Entity(x, y, ENTITY_##name, IMAGE_##name); \
    break;                                              \
  }

  switch (entityByte) {
    case 0x00: {
      entity = Entity(0, 0);
      break;
    }
      ADD_ENTITY(0x01, BLOCK, x, y)
      ADD_ENTITY(0x02, RAMP_TL, x, y)
      ADD_ENTITY(0x03, RAMP_TR, x, y)
    case 0x04:
      break;  // RampBL
    case 0x05:
      break;  // RampBR

      ADD_ENTITY(0x20, SPIKE_DOWN, x + 2, y)
      ADD_ENTITY(0x21, SPIKE_LEFT, x, y)
      ADD_ENTITY(0x22, SPIKE_UP, x + 3, y)
      ADD_ENTITY(0x23, SPIKE_RIGHT, x, y)

      ADD_ENTITY(0x07, CRYS, x, y)
      ADD_ENTITY(0x08, CRYS_BALL, x, y)
      ADD_ENTITY(0x10, RING_VER, x + 2, y)
      ADD_ENTITY(0x11, RING_VER, x + 2, y - 8)
      ADD_ENTITY(0x12, RING_HOR, x, y)
      ADD_ENTITY(0x13, RING_HOR, x - 8, y)
      ADD_ENTITY(0x14, BIG_RING_VER, x + 2, y)
      ADD_ENTITY(0x15, BIG_RING_VER, x + 2, y - 8)
      ADD_ENTITY(0x16, BIG_RING_HOR, x, y)
      ADD_ENTITY(0x17, BIG_RING_HOR, x - 8, y)
      ADD_ENTITY(0x30, DEFLATOR_DOWN, x, y)
      ADD_ENTITY(0x31, DEFLATOR_LEFT, x, y)
      ADD_ENTITY(0x32, DEFLATOR_UP, x, y)
      ADD_ENTITY(0x33, DEFLATOR_RIGHT, x, y)
      ADD_ENTITY(0x34, INFLATOR_DOWN, x + 3, y)
      ADD_ENTITY(0x35, INFLATOR_LEFT, x, y)
      ADD_ENTITY(0x36, INFLATOR_UP, x + 2, y)
      ADD_ENTITY(0x37, INFLATOR_RIGHT, x, y)
      ADD_ENTITY(0xe0, END, x, y)
      ADD_ENTITY(0xe1, END, x - 8, y)
      ADD_ENTITY(0xe2, END, x, y - 8)
      ADD_ENTITY(0xe3, END, x - 8, y - 8)
  }
#undef ADD_ENTITY
};

Rect Entity::rect() {
  if (type == ENTITY_SPIKE_LEFT) return Rect(x, y + 2, 8, 3);
  if (type == ENTITY_SPIKE_RIGHT) return Rect(x, y + 3, 8, 3);
  if (type == ENTITY_INFLATOR_LEFT) return Rect(x, y + 3, 8, 3);
  if (type == ENTITY_INFLATOR_RIGHT) return Rect(x, y + 2, 8, 3);
  if (type == ENTITY_RING_HOR) return Rect(x, y + 2, 16, 4);
  if (type == ENTITY_BIG_RING_HOR) return Rect(x, y + 2, 16, 4);
  if (type == ENTITY_END && level.states.get(this)) return Rect(x + 2, y, 11, 16);

  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};
