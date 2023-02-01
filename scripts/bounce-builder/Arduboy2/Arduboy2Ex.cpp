#include "Arduboy2Ex.h"

#include <Arduino.h>

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
