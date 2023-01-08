#pragma once

#include "constants.h"
#include "game/scene.h"
#include "menus/bounce.h"

typedef void (*funcptr)();

extern Scene scene;
extern Scene prev_scene;

void scene_null();

const funcptr scenes_init[] PROGMEM = {  //
  sceneInitBounce, scene_init_game};

const funcptr scenes_update[] PROGMEM = {  //
  sceneUpdateBounce, scene_update_game};
