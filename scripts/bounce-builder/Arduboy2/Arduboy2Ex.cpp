#include "Arduboy2Ex.h"

#include <Arduino.h>

/* Postponed due to "optimization/code size" ratio
void Arduboy2Ex::fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color) {
  for (int16_t i = x; i < x + w; i++) {
    drawFastVLine(i, y, h, color);
  }
};

void Arduboy2Base::drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color) {
  // Do bounds checks
  if ((x < 0) || (x >= WIDTH) || (y >= HEIGHT) || (h == 0)) return;

  color = (color == WHITE ? 0xff : 0);

  if (y < 0) {
    h += y;
    y = 0;
  }

  int16_t end = min(y + h, HEIGHT) - 1;
  uint8_t data, colorUp = 0xff << (y & 7),
          colorDown = 0xff >> (7 - (end & 7));

  if ((y & 0xf8) == (end & 0xf8)) colorDown &= colorUp;
  else {
    data = sBuffer[y / 8 * WIDTH + x] | colorUp;
    if (!color) data ^= colorUp;
    sBuffer[y / 8 * WIDTH + x] = data;
  }

  for (int16_t i = (y + 7) & 0xf8; i < end - 7; i += 8) {
    sBuffer[i / 8 * WIDTH + x] = color;
  }

  data = sBuffer[end / 8 * WIDTH + x] | colorDown;
  if (!color) data ^= colorDown;
  sBuffer[end / 8 * WIDTH + x] = data;
};
*/

size_t Arduboy2Ex::write(uint8_t c) {
  if (c == '\r') {
  } else if (c == '\n') {
    cursor_x = 0;
    cursor_y += characterHeight;
  } else {
    drawChar(cursor_x, cursor_y, c, textColor);
    cursor_x += (characterWidth + 1);
  }
  return 1;
}

void Arduboy2Ex::drawChar(int16_t x, int16_t y, uint8_t c, uint8_t color) {
  if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) return;

  int16_t index = y / characterHeight * WIDTH + x;

  color = color == WHITE;
  y &= 0x7;

  const uint8_t* bitmap = &font5x7[c * characterWidth];
  uint8_t* buffer = &sBuffer[index];

  bool down = static_cast<size_t>(index + WIDTH) < sizeof(sBuffer);

  for (uint8_t i = 0; i < min(characterWidth, WIDTH - x); ++i) {
    const uint8_t col = pgm_read_byte(bitmap++);

    if (color) {
      *buffer |= col << y;
      if (down) *(buffer + WIDTH) |= col >> (8 - y);
    } else {
      *buffer &= ~(col << y);
      if (down) *(buffer + WIDTH) &= ~(col >> (8 - y));
    }

    buffer++;
  }
}
