#pragma once

#include <Arduboy2.h>

#include "../constants.h"
#include "menu.h"

const char TEXT_NEW_GAME[] PROGMEM = "New game";
const char TEXT_HIGH_SCORE[] PROGMEM = "High score";
const char TEXT_INSTRUCTIONS[] PROGMEM = "Instructions";

const char BOUNCE_TITLE[] PROGMEM = "Bounce";
const char* const BOUNCE_TEXT[] PROGMEM = {TEXT_NEW_GAME, TEXT_HIGH_SCORE, TEXT_INSTRUCTIONS};
const uint8_t BOUNCE_SCENES[] PROGMEM = {SCENE_GAME, SCENE_BOUNCE, SCENE_BOUNCE};

constexpr uint8_t BOUNCE_N PROGMEM = sizeof(BOUNCE_TEXT) / sizeof(BOUNCE_TEXT[0]);

void sceneInitBounce();
void sceneUpdateBounce();
