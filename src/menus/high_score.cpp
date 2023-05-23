#include "high_score.h"

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "../game/level.h"
#include "../scenes.h"

extern Arduboy2Ex arduboy;

void _MenuHighScore::checkEvents() {
  MenuBase::checkEvents();

  if (justPressedOnce(A_BUTTON)) scene = (Scene)pgm_read_byte(scenes);
};

void _MenuHighScore::drawScore() {
  char score[9];

  ultoa(highScore, score, 10);
  uint8_t length = strlen(score), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  uint8_t x = (SCREEN_W - width) / 2,
          y = (SCREEN_H - TITLE_OFFSET_Y - CHAR_HEIGHT) / 2 + TITLE_OFFSET_Y;

  arduboy.setCursor(x, y);
  arduboy.setTextColor(BLACK);
  arduboy.print(score);
};

void _MenuHighScore::sceneInit() {
  arduboy.fillScreen();

  drawTitle(pgm_read_word(text));
  drawScore();

  arduboy.display();
};

void _MenuHighScore::sceneUpdate() {
  checkEvents();
};

_MenuHighScore menuHighScore((char **)&HIGH_SCORE_TEXT, (uint8_t *)&HIGH_SCORE_SCENES);

void sceneInitHighScore() {
  EEPROM.get(EEPROM_HIGH_SCORE, highScore);
  menuHighScore.sceneInit();
};

void sceneUpdateHighScore() {
  menuHighScore.sceneUpdate();
};
