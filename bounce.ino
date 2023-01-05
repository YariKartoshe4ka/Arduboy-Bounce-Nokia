#include <Arduboy2.h>

#include "src/assets.h"
#include "src/ball.h"
#include "src/constants.h"
#include "src/level.h"
#include "src/objects.h"

Arduboy2 arduboy;
Sprites sprites;

Level level;
Entity *area[COLLIDE_AREA_SIZE];

Ball ball;

uint8_t collide_area_size = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(100);

  arduboy.begin();
  arduboy.setFrameRate(FPS);

  ball = Ball(8, 48);
  level = Level(0);
}

void loop() {
  if (!arduboy.nextFrame()) return;

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
}
