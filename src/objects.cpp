#include "objects.h"

#include <Arduboy2.h>

#include "level.h"
#include "utils.h"

extern Arduboy2 arduboy;
extern Sprites sprites;
extern Entity entities[SURFACE_B_H][SURFACE_B_W];
extern Level level;

Rect Entity::rect() {
  return Rect(x, y, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};

Ball::Ball(int16_t x, int16_t y) {
  image = IMAGE_BALL;
  vel_x = vel_y = ac_x = ac_y = 0;
  this->x = x;
  this->y = y;
};

void Ball::check_events() {
  uint8_t state = arduboy.buttonsState();

  if (state & LEFT_BUTTON) ac_x = -BALL_AC_X;
  else if (state & RIGHT_BUTTON) ac_x = BALL_AC_X;
  else ac_x = 0;

  if (state & UP_BUTTON && !(this->state & BALL_STATE_JUMP)) {
    vel_y = -BALL_MAX_VEL_Y;
  }
};

void Ball::move_hor() {
  if (ac_x > 0) vel_x = min(BALL_MAX_VEL_X, vel_x + ac_x);
  else if (ac_x < 0) vel_x = max(-BALL_MAX_VEL_X, vel_x + ac_x);
  else {
    if (vel_x > 0) vel_x = max(0, vel_x - BALL_AC_X);
    else vel_x = min(0, vel_x + BALL_AC_X);
  }

  x += vel_x;
};

void Ball::collide_hor() {
  for (int8_t i = 0; i < SURFACE_B_H; ++i) {
    for (int8_t j = 0; j < SURFACE_B_W; ++j) {
      if (entities[i][j].type == ENTITY_BLOCK) {
        Rect rect_block = entities[i][j].rect(), rect_ball = rect();

        if (arduboy.collide(rect_ball, rect_block)) {
          if (rect_ball.x > rect_block.x) {
            x = rect_block.x + rect_block.width;
            vel_x = -vel_x / 1.6;
          } else if (rect_ball.x < rect_block.x) {
            x = rect_block.x - rect_ball.width;
            vel_x = -vel_x / 1.6;
          }
        }
      }
    }
  }
};

void Ball::move_ver() {
  vel_y += BALL_AC_Y;
  y += vel_y;

  if (vel_y < 0) state |= BALL_STATE_JUMP;
};

void Ball::collide_ver() {
  for (int8_t i = 0; i < SURFACE_B_H; ++i) {
    for (int8_t j = 0; j < SURFACE_B_W; ++j) {
      if (entities[i][j].type == ENTITY_BLOCK) {
        Rect rect_block = entities[i][j].rect(), rect_ball = rect();

        if (arduboy.collide(rect_ball, rect_block)) {
          if (vel_y < 0) {
            y = rect_block.y + rect_block.height;
            vel_y = 0;
          } else if (vel_y > 0) {
            y = rect_block.y - rect_ball.height;
            state &= ~BALL_STATE_JUMP;
            vel_y = -vel_y / 1.6;
          }
        }
      }
    }
  }
};

void Ball::draw() {
  sprites.drawPlusMask(level.offset_x + SURFACE_X + round(x), level.offset_y + round(y), image, 0);
};

Rect Ball::rect() {
  return Rect(round(x), round(y), pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};
