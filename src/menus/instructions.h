#pragma once

#include "../constants.h"
#include "bounce.h"

const char TEXT_INSTRUCTIONS_LONG[] PROGMEM =
  "Guide the ball past many obstacles to pass through all the hoops and open the door to the next "
  "level. Use key LEFT to move the ball left, key UP to move the ball right and key A to bounce "
  "the ball. Watch out for spikes. Use deflators to shrink the ball and inflators to return to "
  "normal size. Large balls float in water, small balls don't. Collect crystals for extra points "
  "and to store your game position. Collect crystal balls to give your ball an extra life. Jump "
  "and speed boosts temporarily boost your powers while rubber floors give you extra bounce.";

const char *const INSTRUCTIONS_TEXT[] PROGMEM = {TEXT_INSTRUCTIONS, TEXT_INSTRUCTIONS_LONG};
const Scene INSTRUCTIONS_SCENES[] PROGMEM = {SCENE_BOUNCE};

class _MenuInstructions : MenuBase {
 private:
  int16_t offsetY;

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
