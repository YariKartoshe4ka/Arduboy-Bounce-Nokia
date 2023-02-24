#include "game_over.h"

#include <Arduboy2Ex.h>

#include "../game/level.h"
#include "../scenes.h"
#include "bounce.h"

extern Arduboy2Ex arduboy;

void _MenuGameOver::checkEvents() {
  MenuBase::checkEvents();

  if (justPressedOnce(A_BUTTON)) scene = (Scene)pgm_read_byte(scenes);
};

void _MenuGameOver::drawScore() {
  char score[9];

  ultoa(level.score, score, 10);

  uint8_t length = strlen(score), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  uint8_t x = (SCREEN_W - width) / 2,
          y = (SCREEN_H - TITLE_OFFSET_Y - CHAR_HEIGHT) / 2 + TITLE_OFFSET_Y;

  arduboy.setCursor(x, y);
  arduboy.setTextColor(WHITE);
  arduboy.print(score);
};

void _MenuGameOver::sceneInit() {
  drawTitle(pgm_read_word(text));
  drawScore();
};

void _MenuGameOver::sceneUpdate() {
  checkEvents();
};

_MenuGameOver menuGameOver((char **)&GAME_OVER_TEXT, (uint8_t *)&GAME_OVER_SCENES);

void sceneInitGameOver() {
  menuBounce = MenuOptions(BOUNCE_TEXT_SIZE, (char **)&BOUNCE_TEXT, (uint8_t *)&BOUNCE_SCENES);
  menuGameOver.sceneInit();
};

void sceneUpdateGameOver() {
  menuGameOver.sceneUpdate();
};
