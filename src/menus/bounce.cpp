#include "bounce.h"

#include <Arduboy2.h>

Menu menuBounce(
  &BOUNCE_N, (char *)&BOUNCE_TITLE, (uint16_t *)&BOUNCE_TEXT, (uint8_t *)&BOUNCE_SCENES
);

void sceneInitBounce() {
  menuBounce.sceneInit();
};

void sceneUpdateBounce() {
  menuBounce.sceneUpdate();
};
