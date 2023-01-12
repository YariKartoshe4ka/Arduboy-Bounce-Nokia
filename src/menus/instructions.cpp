#include "instructions.h"

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "menu.h"

extern Arduboy2Ex arduboy;

#define _LINE_SPACING 1
#define LINE_HEIGHT (CHAR_HEIGHT + _LINE_SPACING)
#define LINE_LENGTH ((SCREEN_W - CHAR_SPACING) / (CHAR_WIDTH + CHAR_SPACING))
#define SURFACE_LINES ((SCREEN_H - TITLE_OFFSET_Y) / LINE_HEIGHT + 1)
#define INSTRUCTIONS_LENGTH (sizeof(TEXT_INSTRUCTIONS_LONG) / sizeof(TEXT_INSTRUCTIONS[0]))

void _MenuInstructions::sceneInit() {
  offsetY = 0;
};

void _MenuInstructions::checkEvents() {
  MenuBase::checkEvents();

  uint8_t state = arduboy.buttonsState();

  if (state & UP_BUTTON) --offsetY;
  else if (state & DOWN_BUTTON) ++offsetY;

  offsetY = min(0, offsetY);
};

void _MenuInstructions::drawInstructions() {
  char c, *ptr = (char *)pgm_read_word(text + 1);

  for (uint8_t i = 0; i < -offsetY / LINE_HEIGHT; ++i) {
    for (uint8_t j = 0; j < LINE_LENGTH; ++j) {
      c = pgm_read_byte(ptr);

      if (c == '\0') return;
      if (!j && c == ' ') --j;

      ++ptr;
    }
  }

  int16_t normalizedOffsetY = offsetY;
  while (normalizedOffsetY <= -LINE_HEIGHT)
    normalizedOffsetY += LINE_HEIGHT;

  for (uint8_t i = 0; i <= (SCREEN_H - TITLE_OFFSET_Y) / LINE_HEIGHT + 1; ++i) {
    arduboy.setCursor(0, normalizedOffsetY + TITLE_OFFSET_Y + i * LINE_HEIGHT);

    for (uint8_t j = 0; j < LINE_LENGTH; ++j) {
      c = pgm_read_byte(ptr);

      if (c == '\0') return;

      if (!j && c == ' ') --j;
      else arduboy.print(c);

      ++ptr;
    }
    if (c != ' ' && pgm_read_byte(ptr) != ' ') arduboy.print('-');
  }
};

void _MenuInstructions::sceneUpdate() {
  checkEvents();

  arduboy.clear();

  drawInstructions();
  drawTitle();

  arduboy.display();
};

_MenuInstructions menuInstructions((char **)&INSTRUCTIONS_TEXT, (uint8_t *)&INSTRUCTIONS_SCENES);

void sceneInitInstructions() {
  menuInstructions.sceneInit();
}

void sceneUpdateInstructions() {
  menuInstructions.sceneUpdate();
}

#undef _LINE_SPACING
#undef LINE_LENGTH
#undef SURFACE_LINES
