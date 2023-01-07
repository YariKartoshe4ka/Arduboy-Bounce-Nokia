#include "root.h"

#include <Arduboy2.h>

Menu menuRoot(&ROOT_N, (char *)&ROOT_TITLE, (uint16_t *)&ROOT_TEXT, (uint8_t *)&ROOT_SCENES);

void sceneInitRoot() {
  menuRoot.sceneInit();
};

void sceneUpdateRoot() {
  menuRoot.sceneUpdate();
};
