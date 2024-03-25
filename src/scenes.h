#pragma once

#include "constants.h"
#include "game/scene.h"
#include "menus/bounce.h"
#include "menus/completed.h"
#include "menus/game_over.h"
#include "menus/high_score.h"
#include "menus/instructions.h"
#include "menus/new_game.h"

typedef void (*funcptr)();

extern Scene scene;
extern Scene prevScene;

const funcptr scenesInit[] PROGMEM = {  //
  sceneInitBounce, sceneInitNewGame,  sceneInitHighScore, sceneInitInstructions,
  sceneInitGame,   sceneInitGameOver, sceneInitCompleted
};

const funcptr scenesUpdate[] PROGMEM = {  //
  sceneUpdateBounce, sceneUpdateNewGame,  sceneUpdateHighScore, sceneUpdateInstructions,
  sceneUpdateGame,   sceneUpdateGameOver, sceneUpdateCompleted
};
