#pragma once

#include "Arduboy2.h"

class Arduboy2Ex : public Arduboy2 {
 public:
  virtual size_t write(uint8_t c);
  static void drawChar(int16_t x, int16_t y, uint8_t c, uint8_t color);
};
