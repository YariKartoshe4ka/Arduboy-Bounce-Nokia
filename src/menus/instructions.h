#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "bounce.h"

const char *const INSTRUCTIONS_TEXT[] PROGMEM = {TEXT_INSTRUCTIONS, TEXT_INSTRUCTIONS_LONG};
const Scene INSTRUCTIONS_SCENES[] PROGMEM = {SCENE_BOUNCE};

class _MenuInstructions : MenuBase {
 private:
  int16_t prevOffsetY, offsetY;

 protected:
  void checkEvents();
  void drawInstructions();

 public:
  void sceneInit();
  void sceneUpdate();

  _MenuInstructions(char **text, uint8_t *scenes) : MenuBase(text, scenes) {}
};

void sceneInitInstructions();
void sceneUpdateInstructions();
