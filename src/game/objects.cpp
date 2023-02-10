#include "objects.h"

#include <Arduboy2Ex.h>

#include "level.h"

Rect Entity::rect() {
  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};

Rect RingHor::rect() {
  return Rect(x, y + 2, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]) - 4);
}
