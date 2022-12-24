#include <Arduboy2.h>

#include "assets.h"
#include "objects.h"
#include "constants.h"
#include "level.h"


Arduboy2 arduboy;
Sprites sprites;

Level level;
Entity entities[SURFACE_B_H][SURFACE_B_W];

Ball ball;

uint32_t prev_millis = 0;
int16_t prev_shift_x = 0;


#define modsub(x, m) (x >= 0 ? (x >= m ? x - m : x) : x + m)


void setup() {
  arduboy.begin();
  arduboy.flashlight();

  arduboy.setFrameRate(FPS);

  ball = Ball(8, 48);

  level.init(0);

  for (int8_t i = 0; i < SURFACE_B_H; ++i)
    for (int8_t j = 0; j < SURFACE_B_W; ++j)
      level.load_entity(i, j, i, j);

  for (int8_t i = 0; i < 16; ++i)
    stars[i] = {1, 2, 3, 4, 5, 6, 7};
}

void loop() {
  if (!arduboy.nextFrame())
    return;

  if (millis() < 3000) {
    sprites.drawOverwrite(0, 0, IMAGE_PRESPLASH, 0);
    arduboy.delayShort(100);
    arduboy.display();
    return;
  }

  arduboy.clear();

  ball.check_events();
  ball.update();

  int16_t offset_x = 0, offset_y = 0, ball_centerx = round(ball.centerx());
  if (ball_centerx > SURFACE_W / 2)
    offset_x = max(SURFACE_W / 2 - ball_centerx, SURFACE_W - level.width * 8);

  int16_t shift_x = -offset_x / 8;
  level.move_hor(shift_x - prev_shift_x);
  prev_shift_x = shift_x;
  // for (int8_t i = 0; i < SURFACE_B_H; ++i)
  //   for (int8_t j = 0; j < SURFACE_B_W; ++j)
  //     level.load_entity(i, j, i, j + level_shift_x);

  for (int16_t k = level.right_bound; k < level.right_bound + SURFACE_B_W; ++k) {
    int16_t j = modsub(k, SURFACE_B_W);
    for (int16_t i = 0; i < SURFACE_B_H; ++i) {
      if (entities[i][j].type == ENTITY_BLOCK) {
        sprites.drawOverwrite(
          offset_x + SURFACE_X + entities[i][j].x,
          entities[i][j].y,
          entities[i][j].image,
          0
        );
      }
    }
  }

  sprites.drawPlusMask(round(offset_x + SURFACE_X + ball.x), round(ball.y), ball.image, 0);

  // Clear outside surface
  arduboy.fillRect(0, 0, SURFACE_X, SCREEN_H, BLACK);
  arduboy.fillRect(SURFACE_X + SURFACE_W, 0, SURFACE_X, SCREEN_H, BLACK);
  arduboy.drawLine(SURFACE_X - 2, 0, SURFACE_X - 2, SCREEN_H);
  arduboy.drawLine(SURFACE_X + SURFACE_W + 1, 0, SURFACE_X + SURFACE_W + 1, SCREEN_H);

  // uint32_t cur_millis = millis();
  // arduboy.print(1000. / (cur_millis - prev_millis));
  // prev_millis = cur_millis;

  arduboy.display();
}
