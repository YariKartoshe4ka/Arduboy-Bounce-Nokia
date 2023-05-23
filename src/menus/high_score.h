#pragma once

#include "../assets/texts.h"
#include "../constants.h"

const char *const HIGH_SCORE_TEXT[] PROGMEM = {TEXT_HIGH_SCORE};
const Scene HIGH_SCORE_SCENES[] PROGMEM = {Scene::BOUNCE};

void sceneInitHighScore();
void sceneUpdateHighScore();
