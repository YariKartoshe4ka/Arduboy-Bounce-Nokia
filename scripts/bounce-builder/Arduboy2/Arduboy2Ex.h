#pragma once

#include "Arduboy2.h"

class Arduboy2Ex : public Arduboy2 {
 public:
  static void fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color = WHITE);
  static void drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color = WHITE);
};
