#include "completed.h"

#include <Arduboy2Ex.h>
#include <EEPROM.h>

#include "../constants.h"
#include "../game/level.h"
#include "../scenes.h"

extern Arduboy2Ex arduboy;

MenuScore menuCompleted((char **)&COMPLETED_TEXT, (uint8_t *)&COMPLETED_SCENES, &level.score);

void sceneInitCompleted() {
  if (level.score > highScore) {
    highScore = level.score;
    EEPROM.put(EEPROM_HIGH_SCORE, highScore);
  }
  menuCompleted.text += level.levelNo;
  menuCompleted.sceneInit();
  menuCompleted.text -= level.levelNo;
};

void sceneUpdateCompleted() {
  menuCompleted.sceneUpdate();
};
