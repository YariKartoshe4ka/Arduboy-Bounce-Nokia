#include <Arduboy2Ex.h>

#include "src/scenes.h"

Arduboy2Ex arduboy;
Sprites sprites;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(100);

  arduboy.begin();
  arduboy.setFrameRate(FPS);
  arduboy.invert(1);
}

void loop() {
  if (!arduboy.nextFrame()) return;

  if (scene != prevScene) {
    funcptr(pgm_read_word(&scenesInit[(uint8_t)scene]))();
    prevScene = scene;
  }
  funcptr(pgm_read_word(&scenesUpdate[(uint8_t)scene]))();
}
