#include "objects.h"

#include <Arduboy2.h>

#include "level.h"
#include "utils.h"

extern Arduboy2 arduboy;
extern Sprites sprites;
extern Entity entities[SURFACE_B_H][SURFACE_B_W];
extern Level level;

Rect Entity::rect() {
  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};
