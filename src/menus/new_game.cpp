#include "new_game.h"

#include <Arduboy2.h>

MenuOptions menuNewGame(
  sizeof(NEW_GAME_TEXT) / sizeof(NEW_GAME_TEXT[0]), (char **)&NEW_GAME_TEXT,
  (uint8_t *)NEW_GAME_SCENES
);

void sceneInitNewGame() {
  menuNewGame.sceneInit();
};

void sceneUpdateNewGame() {
  menuNewGame.sceneUpdate();
};
