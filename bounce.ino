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
}

void loop() {
  if (!arduboy.nextFrame()) return;

  if (scene != prevScene) {
    funcptr(pgm_read_word(&scenes_init[(uint8_t)scene]))();
    prevScene = scene;
  }
  funcptr(pgm_read_word(&scenes_update[(uint8_t)scene]))();

  Serial.println(arduboy.cpuLoad());
}
