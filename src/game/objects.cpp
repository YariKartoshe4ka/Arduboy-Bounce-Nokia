#include "objects.h"

#include <Arduboy2Ex.h>

Rect Entity::rect() {
  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};
