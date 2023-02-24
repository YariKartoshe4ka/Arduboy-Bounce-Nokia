#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char *const GAME_OVER_TEXT[] PROGMEM = {TEXT_GAME_OVER};
const Scene GAME_OVER_SCENES[] PROGMEM = {Scene::BOUNCE};

class _MenuGameOver : MenuBase {
 protected:
  void checkEvents();
  void drawScore();

 public:
  void sceneInit();
  void sceneUpdate();

  _MenuGameOver(char **text, uint8_t *scenes) : MenuBase(text, scenes){};
};

void sceneInitGameOver();
void sceneUpdateGameOver();
