#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char *const COMPLETED_TEXT[] PROGMEM = {  //
  TEXT_LEVEL_1_COMPLETED, TEXT_LEVEL_2_COMPLETED, TEXT_LEVEL_3_COMPLETED, TEXT_LEVEL_4_COMPLETED,
  TEXT_LEVEL_5_COMPLETED, TEXT_LEVEL_6_COMPLETED, TEXT_LEVEL_7_COMPLETED
};
const Scene COMPLETED_SCENES[] PROGMEM = {Scene::GAME};

void sceneInitCompleted();
void sceneUpdateCompleted();
