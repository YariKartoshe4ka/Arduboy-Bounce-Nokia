#pragma once

#include "constants.h"
#include "game/scene.h"
#include "menus/bounce.h"
#include "menus/instructions.h"

typedef void (*funcptr)();

extern Scene scene;
extern Scene prev_scene;

void scene_dummy();

const funcptr scenes_init[] PROGMEM = {  //
  sceneInitBounce, sceneInitInstructions, scene_init_game};

const funcptr scenes_update[] PROGMEM = {  //
  sceneUpdateBounce, sceneUpdateInstructions, scene_update_game};
