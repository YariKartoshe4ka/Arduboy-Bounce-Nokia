#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char *const GAME_OVER_TEXT[] PROGMEM = {TEXT_GAME_OVER};
const Scene GAME_OVER_SCENES[] PROGMEM = {Scene::BOUNCE};

void sceneInitGameOver();
void sceneUpdateGameOver();
