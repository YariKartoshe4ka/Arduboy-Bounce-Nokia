#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char *const HIGH_SCORE_TEXT[] PROGMEM = {TEXT_HIGH_SCORE};
const Scene HIGH_SCORE_SCENES[] PROGMEM = {Scene::BOUNCE};

class _MenuHighScore : MenuBase {
 protected:
  void checkEvents();
  void drawScore();

 public:
  void sceneInit();
  void sceneUpdate();

  _MenuHighScore(char **text, uint8_t *scenes) : MenuBase(text, scenes){};
};

void sceneInitHighScore();
void sceneUpdateHighScore();
