#include "objects.h"

#include <Arduboy2Ex.h>

#include "level.h"

Rect Entity::rect() {
  if (type == ENTITY_RING_HOR)
    return Rect(x, y + 2, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]) - 4);

  if (type == ENTITY_BIG_RING_HOR)
    return Rect(x, y + 2, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]) - 4);

  if (type == ENTITY_END && level.states.get(this))
    return Rect(x + 2, y, pgm_read_byte(&image[0]) - 5, pgm_read_byte(&image[1]));

  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};
