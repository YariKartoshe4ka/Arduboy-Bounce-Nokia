#include "scene.h"

#include <Arduboy2.h>

#include "../constants.h"
#include "ball.h"
#include "level.h"

extern Arduboy2 arduboy;

Ball ball;
Level level;
Entity *area[COLLIDE_AREA_SIZE];

void scene_init_game() {
  Serial.println(1);
  ball = Ball(8, 48);
  level = Level(0);
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
  level.draw();
  ball.draw();

  // Clear outside surface
  arduboy.fillRect(SURFACE_X - 10, 0, 10, SCREEN_H, BLACK);
  arduboy.fillRect(SURFACE_X + SURFACE_W, 0, 12, SCREEN_H, BLACK);
  arduboy.drawLine(SURFACE_X - 2, 0, SURFACE_X - 2, SCREEN_H);
  arduboy.drawLine(SURFACE_X + SURFACE_W + 1, 0, SURFACE_X + SURFACE_W + 1, SCREEN_H);

  arduboy.display();
};
