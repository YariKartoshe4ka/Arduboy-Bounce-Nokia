#include <Arduboy2Ex.h>
#include <EEPROM.h>

#include "src/scenes.h"

Arduboy2Ex arduboy;
Sprites sprites;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(100);

  arduboy.begin();
  arduboy.setFrameRate(FPS);

  uint32_t x = 0;
  EEPROM.put(EEPROM_HIGH_SCORE, x);
}

void loop() {
  if (!arduboy.nextFrame()) return;

  if (scene != prevScene) {
    funcptr(pgm_read_word(&scenesInit[(uint8_t)scene]))();
    prevScene = scene;
  }
  funcptr(pgm_read_word(&scenesUpdate[(uint8_t)scene]))();
}
