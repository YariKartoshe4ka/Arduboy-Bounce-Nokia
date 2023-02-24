#include "scene.h"

#include <Arduboy2Ex.h>

#include "../assets/levels.h"
#include "../constants.h"
#include "../menus/new_game.h"
#include "../scenes.h"
#include "ball.h"
#include "level.h"

extern Arduboy2Ex arduboy;

void sceneInitGame() {
  if (prevScene == Scene::BOUNCE) return;

  menuBounce = MenuOptions(PAUSE_TEXT_SIZE, (char **)&PAUSE_TEXT, (uint8_t *)&PAUSE_SCENES);

  level = Level(menuNewGame.choice - 1);
  ball = Ball(level[0] * 8, level[1] * 8);
  level.moveVer();
};

void sceneUpdateGame() {
  arduboy.clear();

  ball.checkEvents();

  ball.moveHor();
  level.moveHor();
  ball.collideHor();

  ball.moveVer();
  level.moveVer();
  ball.collideVer();

  level.updateOffsets();
  level.drawSurface();
  ball.draw();

  // Clear outside surface
  arduboy.fillRect(0, 0, SURFACE_X, SCREEN_H, BLACK);
  arduboy.fillRect(SCREEN_W - SURFACE_X, 0, SURFACE_X, SCREEN_H, BLACK);

  arduboy.drawFastVLine(SURFACE_X - 2, 0, SCREEN_H, WHITE);
  arduboy.drawFastVLine(SCREEN_W - SURFACE_X + 1, 0, SCREEN_H, WHITE);

  level.drawInterface();

  arduboy.setCursor(WIDTH - 11, 0);
  arduboy.println(arduboy.cpuLoad());

  arduboy.display();
};
