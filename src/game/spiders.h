#pragma once

#include <Arduboy2Ex.h>

#include "level.h"

#define SPIDERS_AMOUNT 20
#define SPIDER_SPEED 0.4

struct Spider {
  int16_t x, y, dx, dy;
  uint8_t tx, ty;

  Spider() = default;
  Spider(int16_t x, int16_t y, int16_t dx, int16_t dy, uint8_t tx, uint8_t ty)
      : x(x * 8), y(y * 8), dx(dx * 8), dy(dy * 8), tx(tx), ty(ty){};

  int16_t getX(int16_t ticks);
  int16_t getY(int16_t ticks);

  void draw();
};

class Spiders {
  uint8_t n = 0;
  Spider _spiders[SPIDERS_AMOUNT];

 public:
  Spiders() = default;
  void init(Level& level);

  void draw();
};

extern Spiders spiders;
