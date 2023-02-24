#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char *const COMPLETED_TEXT[] PROGMEM = {  //
  TEXT_LEVEL_1_COMPLETED, TEXT_LEVEL_2_COMPLETED, TEXT_LEVEL_3_COMPLETED, TEXT_LEVEL_4_COMPLETED,
  TEXT_LEVEL_5_COMPLETED, TEXT_LEVEL_6_COMPLETED, TEXT_LEVEL_7_COMPLETED};
const Scene COMPLETED_SCENES[] PROGMEM = {Scene::GAME};

class _MenuCompleted : MenuBase {
 protected:
  void checkEvents();
  void drawScore();

 public:
  void sceneInit();
  void sceneUpdate();

  _MenuCompleted(char **text, uint8_t *scenes) : MenuBase(text, scenes){};
};

void sceneInitCompleted();
void sceneUpdateCompleted();
