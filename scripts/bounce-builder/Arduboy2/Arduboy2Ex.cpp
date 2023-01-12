#include "Arduboy2Ex.h"

#include <Arduino.h>

void Arduboy2Ex::fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color) {
  for (int16_t i = x; i < x + w; i++) {
    drawFastVLine(i, y, h, color);
  }
};

void Arduboy2Ex::drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color) {
  if (x < 0 || x >= WIDTH || y >= HEIGHT) return;

  color = (color == WHITE ? ~0 : 0);

  if (y < 0) {
    h += y;
    y = 0;
  }

  int16_t end = y + h;
  uint8_t data, colorUp = 0xff << (y - (y & 0xf8)),
                colorDown = 0xff >> (8 - (min(end, HEIGHT - 1) & 7));

  data = sBuffer[(y & 0xf8) * WIDTH / 8 + x] | colorUp;
  if (!color) data ^= colorUp;
  sBuffer[(y & 0xf8) * WIDTH / 8 + x] = data;

  for (uint8_t i = max(y + 7, 0) & 0xf8; i <= min(end, HEIGHT - 1) - 7; i += 8) {
    sBuffer[i * WIDTH / 8 + x] = color;
  }

  data = sBuffer[(min(end, HEIGHT - 1) & 0xf8) * WIDTH / 8 + x] | colorDown;
  if (!color) data ^= colorDown;
  sBuffer[(min(end, HEIGHT - 1) & 0xf8) * WIDTH / 8 + x] = data;
};
