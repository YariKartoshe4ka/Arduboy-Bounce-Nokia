#include "bounce.h"

#include <Arduboy2Ex.h>

MenuOptions menuBounce(
  sizeof(BOUNCE_TEXT) / sizeof(BOUNCE_TEXT[0]), (char **)&BOUNCE_TEXT, (uint8_t *)&BOUNCE_SCENES
);

void sceneInitBounce() {
  menuBounce.sceneInit();
};

void sceneUpdateBounce() {
  menuBounce.sceneUpdate();
};
