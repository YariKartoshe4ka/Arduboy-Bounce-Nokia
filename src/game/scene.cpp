#include "scene.h"

#include <Arduboy2.h>

#include "../assets/levels.h"
#include "../constants.h"
#include "../menus/new_game.h"
#include "../scenes.h"
#include "ball.h"
#include "level.h"
#include "spiders.h"

extern Arduboy2 arduboy;

void sceneInitGame() {
  if (prevScene == Scene::BOUNCE) return;

  menuBounce = MenuOptions(PAUSE_TEXT_SIZE, (char **)&PAUSE_TEXT, (uint8_t *)&PAUSE_SCENES);

  if (prevScene == Scene::NEW_GAME) level.init(menuNewGame.choice - 1, 0);
  else level.init(level.levelNo + 1, level.score);

  ball.init(
    level[0] * 8, level[1] * 8, prevScene == Scene::NEW_GAME ? 3 : ball.lives,
    BALL_STATE_BIG * level[2]
  );

  spiders.init(level);

  level.moveVer();
};

void sceneUpdateGame() {
  arduboy.fillScreen();

  ball.checkEvents();

  ball.moveHor();
  level.moveHor();
  ball.collideHor();

  ball.moveVer();
  level.moveVer();
  ball.collideVer();

  level.updateOffsets();
  spiders.draw();
  level.drawSurface();
  ball.draw();

  // Clear outside surface
  arduboy.fillRect(0, 0, SURFACE_X, SCREEN_H);
  arduboy.fillRect(SCREEN_W - SURFACE_X, 0, SURFACE_X, SCREEN_H);

  arduboy.drawFastVLine(SURFACE_X - 2, 0, SCREEN_H, BLACK);
  arduboy.drawFastVLine(SCREEN_W - SURFACE_X + 1, 0, SCREEN_H, BLACK);

  level.drawInterface();

  arduboy.setCursor(WIDTH - 11, 0);
  arduboy.println(arduboy.cpuLoad());

  arduboy.display();

  if (ball.state & BALL_STATE_POP) {
    arduboy.delayShort(300);
    ball.reset();
  }
};
