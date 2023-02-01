#pragma once

#include "constants.h"
#include "game/scene.h"
#include "menus/bounce.h"
#include "menus/instructions.h"
#include "menus/new_game.h"

typedef void (*funcptr)();

extern Scene scene;
extern Scene prev_scene;

void scene_dummy();

const funcptr scenes_init[] PROGMEM = {  //
  sceneInitBounce, sceneInitNewGame, sceneInitInstructions, scene_init_game};

const funcptr scenes_update[] PROGMEM = {  //
  sceneUpdateBounce, sceneUpdateNewGame, sceneUpdateInstructions, scene_update_game};
