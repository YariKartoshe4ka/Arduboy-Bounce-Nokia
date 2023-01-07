#pragma once

#include "constants.h"
#include "game/scene.h"
#include "menus/root.h"

typedef void (*funcptr)();

extern uint8_t scene;
extern uint8_t prev_scene;

void scene_null();

const funcptr scenes_init[] PROGMEM = {  //
  sceneInitRoot, scene_init_game};

const funcptr scenes_update[] PROGMEM = {  //
  sceneUpdateRoot, scene_update_game};
