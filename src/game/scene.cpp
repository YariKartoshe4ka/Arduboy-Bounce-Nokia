#include "scene.h"

#include <Arduboy2Ex.h>

#include "../assets/levels.h"
#include "../constants.h"
#include "../menus/new_game.h"
#include "../scenes.h"
#include "ball.h"
#include "level.h"

extern Arduboy2Ex arduboy;

void scene_init_game() {
  if (prevScene == Scene::BOUNCE) return;

  menuBounce = MenuOptions(
    sizeof(PAUSE_TEXT) / sizeof(PAUSE_TEXT[0]), (char **)&PAUSE_TEXT, (uint8_t *)&PAUSE_SCENES
  );

  level = Level(menuNewGame.choice - 1);
  ball = Ball(level[0] * 8, level[1] * 8);
  level.move_ver();
};

void scene_update_game() {
  arduboy.clear();

  ball.check_events();

  ball.move_hor();
  level.move_hor();
  ball.collide_hor();

  ball.move_ver();
  level.move_ver();
  ball.collide_ver();

  level.update_offsets();
  level.draw_surface();
  ball.draw();

  // Clear outside surface
  arduboy.fillRect(0, 0, SURFACE_X, SCREEN_H, BLACK);
  arduboy.fillRect(SCREEN_W - SURFACE_X, 0, SURFACE_X, SCREEN_H, BLACK);

  arduboy.drawFastVLine(SURFACE_X - 2, 0, SCREEN_H, WHITE);
  arduboy.drawFastVLine(SCREEN_W - SURFACE_X + 1, 0, SCREEN_H, WHITE);

  level.draw_interface();

  arduboy.setCursor(WIDTH - 11, 0);
  arduboy.println(arduboy.cpuLoad());

  arduboy.display();
};
