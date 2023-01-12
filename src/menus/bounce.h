#pragma once

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "menu.h"

const char BOUNCE_TITLE[] PROGMEM = "Bounce";
const char TEXT_NEW_GAME[] PROGMEM = "New game";
const char TEXT_HIGH_SCORE[] PROGMEM = "High score";
const char TEXT_INSTRUCTIONS[] PROGMEM = "Instructions";

const char* const BOUNCE_TEXT[] PROGMEM = {
  BOUNCE_TITLE, TEXT_NEW_GAME, TEXT_HIGH_SCORE, TEXT_INSTRUCTIONS};
const Scene BOUNCE_SCENES[] PROGMEM = {SCENE_BOUNCE, SCENE_GAME, SCENE_BOUNCE, SCENE_INSTRUCTIONS};

void sceneInitBounce();
void sceneUpdateBounce();
