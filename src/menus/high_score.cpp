#include "high_score.h"

#include <Arduboy2.h>

#include "../constants.h"
#include "../game/level.h"
#include "../storage.h"
#include "menu.h"

MenuScore menuHighScore(
  (char **)&HIGH_SCORE_TEXT, (uint8_t *)&HIGH_SCORE_SCENES, &storage_highScore
);

void sceneInitHighScore() {
  menuHighScore.sceneInit();
};

void sceneUpdateHighScore() {
  menuHighScore.sceneUpdate();
};
