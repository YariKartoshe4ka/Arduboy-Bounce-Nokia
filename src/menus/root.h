#pragma once

#include <Arduboy2.h>

#include "../constants.h"
#include "menu.h"

const char TEXT_NEW_GAME[] PROGMEM = "New game";
const char TEXT_HIGH_SCORE[] PROGMEM = "High score";
const char TEXT_INSTRUCTIONS[] PROGMEM = "Instructions";

const char ROOT_TITLE[] PROGMEM = "Bounce";
const char* const ROOT_TEXT[] PROGMEM = {TEXT_NEW_GAME, TEXT_HIGH_SCORE, TEXT_INSTRUCTIONS};
const uint8_t ROOT_SCENES[] PROGMEM = {SCENE_GAME, SCENE_ROOT, SCENE_ROOT};

constexpr uint8_t ROOT_N PROGMEM = sizeof(ROOT_TEXT) / sizeof(ROOT_TEXT[0]);

void sceneInitRoot();
void sceneUpdateRoot();
