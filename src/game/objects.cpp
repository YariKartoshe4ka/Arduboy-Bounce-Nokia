#include "objects.h"

#include <Arduboy2.h>

#include "level.h"

void loadEntity(Entity &entity, uint16_t x, uint16_t y) {
  uint8_t entityByte = level[8 + y * level.width + x];

  x *= 8;
  y *= 8;

  switch (entityByte) {
    case 0x00: {
      entity = Entity(0, 0);
      break;
    }
    case 0x01: {
      entity = Entity(x, y, ENTITY_BLOCK, IMAGE_BLOCK);
      break;
    }
    case 0x02: {
      entity = Entity(x, y, ENTITY_RAMP_TL, IMAGE_RAMP_TL);
      break;
    }
    case 0x03: {
      entity = Entity(x, y, ENTITY_RAMP_TR, IMAGE_RAMP_TR);
      break;
    }
    case 0x04:
      break;  // RampBL
    case 0x05:
      break;  // RampBR
    case 0x20: {
      entity = Entity(x + 2, y, ENTITY_SPIKE_DOWN, IMAGE_SPIKE_DOWN);
      break;
    }
    case 0x21: {
      entity = Entity(x, y, ENTITY_SPIKE_LEFT, IMAGE_SPIKE_LEFT);
      break;
    }
    case 0x22: {
      entity = Entity(x + 3, y, ENTITY_SPIKE_UP, IMAGE_SPIKE_UP);
      break;
    }
    case 0x23: {
      entity = Entity(x, y, ENTITY_SPIKE_RIGHT, IMAGE_SPIKE_RIGHT);
      break;
    }
    case 0x07: {
      entity = Entity(x, y, ENTITY_CRYS, IMAGE_CRYS);
      break;
    }
    case 0x08: {
      entity = Entity(x, y, ENTITY_CRYS_BALL, IMAGE_CRYS_BALL);
      break;
    }
    case 0x10: {
      entity = Entity(x + 2, y, ENTITY_RING_VER, IMAGE_RING_VER);
      break;
    }
    case 0x11: {
      entity = Entity(x + 2, y - 8, ENTITY_RING_VER, IMAGE_RING_VER);
      break;
    }
    case 0x12: {
      entity = Entity(x, y, ENTITY_RING_HOR, IMAGE_RING_HOR);
      break;
    }
    case 0x13: {
      entity = Entity(x - 8, y, ENTITY_RING_HOR, IMAGE_RING_HOR);
      break;
    }
    case 0x14: {
      entity = Entity(x + 2, y, ENTITY_BIG_RING_VER, IMAGE_BIG_RING_VER);
      break;
    }
    case 0x15: {
      entity = Entity(x + 2, y - 8, ENTITY_BIG_RING_VER, IMAGE_BIG_RING_VER);
      break;
    }
    case 0x16: {
      entity = Entity(x, y, ENTITY_BIG_RING_HOR, IMAGE_BIG_RING_HOR);
      break;
    }
    case 0x17: {
      entity = Entity(x - 8, y, ENTITY_BIG_RING_HOR, IMAGE_BIG_RING_HOR);
      break;
    }
    case 0x30: {
      entity = Entity(x, y, ENTITY_DEFLATOR_DOWN, IMAGE_DEFLATOR_DOWN);
      break;
    }
    case 0x31: {
      entity = Entity(x, y, ENTITY_DEFLATOR_LEFT, IMAGE_DEFLATOR_LEFT);
      break;
    }
    case 0x32: {
      entity = Entity(x, y, ENTITY_DEFLATOR_UP, IMAGE_DEFLATOR_UP);
      break;
    }
    case 0x33: {
      entity = Entity(x, y, ENTITY_DEFLATOR_RIGHT, IMAGE_DEFLATOR_RIGHT);
      break;
    }
    case 0x34: {
      entity = Entity(x + 3, y, ENTITY_INFLATOR_DOWN, IMAGE_INFLATOR_DOWN);
      break;
    }
    case 0x35: {
      entity = Entity(x, y, ENTITY_INFLATOR_LEFT, IMAGE_INFLATOR_LEFT);
      break;
    }
    case 0x36: {
      entity = Entity(x + 2, y, ENTITY_INFLATOR_UP, IMAGE_INFLATOR_UP);
      break;
    }
    case 0x37: {
      entity = Entity(x, y, ENTITY_INFLATOR_RIGHT, IMAGE_INFLATOR_RIGHT);
      break;
    }
    case 0xe0: {
      entity = Entity(x, y, ENTITY_END, IMAGE_END);
      break;
    }
    case 0xe1: {
      entity = Entity(x - 8, y, ENTITY_END, IMAGE_END);
      break;
    }
    case 0xe2: {
      entity = Entity(x, y - 8, ENTITY_END, IMAGE_END);
      break;
    }
    case 0xe3: {
      entity = Entity(x - 8, y - 8, ENTITY_END, IMAGE_END);
      break;
    }
  }
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
