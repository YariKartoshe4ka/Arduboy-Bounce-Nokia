#include "completed.h"

#include <Arduboy2.h>

#include "../constants.h"
#include "../game/level.h"
#include "../scenes.h"
#include "../storage.h"

extern Arduboy2 arduboy;

MenuScore menuCompleted((char **)&COMPLETED_TEXT, (uint8_t *)&COMPLETED_SCENES, &level.score);

void sceneInitCompleted() {
  storageUpdateHighScore(level.score);
  menuCompleted.text += level.levelNo;
  menuCompleted.sceneInit();
  menuCompleted.text -= level.levelNo;
};

void sceneUpdateCompleted() {
  menuCompleted.sceneUpdate();
};
