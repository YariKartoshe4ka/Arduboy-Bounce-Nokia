#include "spiders.h"

#include <Arduboy2Ex.h>

#include "../assets/images.h"
#include "../constants.h"
#include "level.h"

extern Arduboy2Ex arduboy;
extern Sprites sprites;

Spiders spiders;

int16_t Spider::getX(int16_t ticks) {
  if (!dx) return x;
  int16_t p = dx / SPIDER_SPEED;
  return x + dx - SPIDER_SPEED * abs((ticks + tx) % (2 * p) - p);
};

int16_t Spider::getY(int16_t ticks) {
  if (!dy) return y;
  int16_t p = dy / SPIDER_SPEED;
  return y + dy - SPIDER_SPEED * abs((ticks + ty) % (2 * p) - p);
};

void Spider::draw() {
  sprites.drawOverwrite(
    level.offsetX + SURFACE_X + getX(spiders.ticks), level.offsetY + getY(spiders.ticks),
    IMAGE_SPIDER, 0
  );
};

void Spiders::init(Level& level) {
  ticks = 0;

  uint8_t m = level[8 + (uint16_t)level.width * level.height];

  for (n = 0; n < m; ++n) {
    uint16_t j = n * 6 + 9 + (uint16_t)level.width * level.height;
    _spiders[n] =
      Spider(level[j], level[j + 1], level[j + 2], level[j + 3], level[j + 4], level[j + 5]);
  }
};

void Spiders::draw() {
  ++ticks;

  for (uint8_t i = 0; i < n; ++i)
    _spiders[i].draw();
};
