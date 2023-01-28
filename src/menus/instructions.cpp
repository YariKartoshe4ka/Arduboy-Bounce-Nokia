#include "instructions.h"

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "menu.h"

extern Arduboy2Ex arduboy;

#define LINE_HEIGHT (CHAR_HEIGHT + 1)
#define SURFACE_LINES ((SCREEN_H - TITLE_OFFSET_Y) / LINE_HEIGHT + 2)

void _MenuInstructions::sceneInit() {
  prevOffsetY = -1;
  offsetY = 0;
};

void _MenuInstructions::checkEvents() {
  MenuBase::checkEvents();

  uint8_t state = arduboy.buttonsState();

  if (state & UP_BUTTON) --offsetY;
  else if (state & DOWN_BUTTON) ++offsetY;

  offsetY = max(
    HEIGHT - TITLE_OFFSET_Y
      - int16_t(sizeof(TEXT_INSTRUCTIONS_LONG) / sizeof(TEXT_INSTRUCTIONS_LONG[0])) * LINE_HEIGHT,
    min(0, offsetY)
  );
};

void _MenuInstructions::drawInstructions() {
  arduboy.setTextColor(WHITE);

  char **ptr = (char **)pgm_read_word(text + 1);

  int16_t normalizedOffsetY = offsetY % LINE_HEIGHT;

  ptr += -offsetY / LINE_HEIGHT;

  for (uint8_t i = 0; i < SURFACE_LINES; ++i) {
    arduboy.setCursor(1, normalizedOffsetY + TITLE_OFFSET_Y + i * LINE_HEIGHT);
    arduboy.print((FlashString)pgm_read_word(ptr));
    ++ptr;
  }
};

void _MenuInstructions::sceneUpdate() {
  checkEvents();

  if (prevOffsetY == offsetY) return;
  prevOffsetY = offsetY;

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

#undef LINE_HEIGHT
#undef SURFACE_LINES
