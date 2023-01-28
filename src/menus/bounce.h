#pragma once

#include <Arduboy2Ex.h>

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char* const BOUNCE_TEXT[] PROGMEM = {
  TEXT_BOUNCE, TEXT_NEW_GAME, TEXT_HIGH_SCORE, TEXT_INSTRUCTIONS};
const Scene BOUNCE_SCENES[] PROGMEM = {SCENE_BOUNCE, SCENE_GAME, SCENE_BOUNCE, SCENE_INSTRUCTIONS};

void sceneInitBounce();
void sceneUpdateBounce();
