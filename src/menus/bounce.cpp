#include "bounce.h"

#include <Arduboy2.h>

Menu menuBounce(
  &BOUNCE_N, (char *)&BOUNCE_TITLE, (const char **)&BOUNCE_TEXT, (uint8_t *)&BOUNCE_SCENES
);

void sceneInitBounce() {
  menuBounce.sceneInit();
};

void sceneUpdateBounce() {
  menuBounce.sceneUpdate();
};
