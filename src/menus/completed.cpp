#include "completed.h"

#include <Arduboy2Ex.h>

#include "../game/level.h"
#include "../scenes.h"

extern Arduboy2Ex arduboy;

void _MenuCompleted::checkEvents() {
  MenuBase::checkEvents();

  if (justPressedOnce(A_BUTTON)) scene = (Scene)pgm_read_byte(scenes);
};

void _MenuCompleted::drawScore() {
  char score[9];

  ultoa(level.score, score, 10);
  uint8_t length = strlen(score), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  uint8_t x = (SCREEN_W - width) / 2,
          y = (SCREEN_H - TITLE_OFFSET_Y - CHAR_HEIGHT) / 2 + TITLE_OFFSET_Y;

  arduboy.setCursor(x, y);
  arduboy.setTextColor(BLACK);
  arduboy.print(score);
};

void _MenuCompleted::sceneInit() {
  arduboy.fillScreen();

  drawTitle(pgm_read_word(text + level.levelNo));
  drawScore();

  arduboy.display();
};

void _MenuCompleted::sceneUpdate() {
  checkEvents();
};

_MenuCompleted menuCompleted((char **)&COMPLETED_TEXT, (uint8_t *)&COMPLETED_SCENES);

void sceneInitCompleted() {
  menuCompleted.sceneInit();
};

void sceneUpdateCompleted() {
  menuCompleted.sceneUpdate();
};
