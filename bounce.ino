#include <Arduboy2.h>

#include "src/scenes.h"

Arduboy2 arduboy;
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

  if (scene != prev_scene) scenes_init[scene]();
  scenes_update[scene]();

  prev_scene = scene;
}
