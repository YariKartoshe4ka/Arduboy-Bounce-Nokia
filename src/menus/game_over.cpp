#include "game_over.h"

#include <Arduboy2Ex.h>

#include "../game/level.h"
#include "../scenes.h"
#include "../storage.h"
#include "bounce.h"

extern Arduboy2Ex arduboy;

MenuScore menuGameOver((char **)&GAME_OVER_TEXT, (uint8_t *)&GAME_OVER_SCENES, &level.score);

void sceneInitGameOver() {
  storageUpdateHighScore(level.score);
  menuBounce = MenuOptions(BOUNCE_TEXT_SIZE, (char **)&BOUNCE_TEXT, (uint8_t *)&BOUNCE_SCENES);
  menuGameOver.sceneInit();
};

void sceneUpdateGameOver() {
  menuGameOver.sceneUpdate();
};
