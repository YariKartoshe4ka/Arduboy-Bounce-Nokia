#include "high_score.h"

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "../game/level.h"
#include "menu.h"

MenuScore menuHighScore((char **)&HIGH_SCORE_TEXT, (uint8_t *)&HIGH_SCORE_SCENES, &highScore);

void sceneInitHighScore() {
  EEPROM.get(EEPROM_HIGH_SCORE, highScore);
  menuHighScore.sceneInit();
};

void sceneUpdateHighScore() {
  menuHighScore.sceneUpdate();
};
