#pragma once

#include "constants.h"
#include "game/scene.h"
#include "menus/bounce.h"
#include "menus/game_over.h"
#include "menus/instructions.h"
#include "menus/new_game.h"

typedef void (*funcptr)();

extern Scene scene;
extern Scene prevScene;

const funcptr scenesInit[] PROGMEM = {  //
  sceneInitBounce, sceneInitNewGame, sceneInitInstructions, sceneInitGame, sceneInitGameOver};

const funcptr scenesUpdate[] PROGMEM = {  //
  sceneUpdateBounce, sceneUpdateNewGame, sceneUpdateInstructions, sceneUpdateGame,
  sceneUpdateGameOver};
