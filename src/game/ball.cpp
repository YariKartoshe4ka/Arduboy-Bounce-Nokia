#include "ball.h"

#include <Arduboy2.h>

#include "../constants.h"
#include "objects.h"
#include "scene.h"

extern Arduboy2 arduboy;
extern Sprites sprites;

Ball::Ball(int16_t x, int16_t y) {
  image = IMAGE_BALL;
  vel_x = vel_y = ac_x = 0;
  this->x = x;
  this->y = y;
};

void Ball::check_events() {
  uint8_t state = arduboy.buttonsState();

  if (state & LEFT_BUTTON) ac_x = -BALL_AC_X;
  else if (state & RIGHT_BUTTON) ac_x = BALL_AC_X;
  else ac_x = 0;

  if (state & UP_BUTTON && !(this->state & BALL_STATE_JUMP)) {
    state |= BALL_STATE_JUMP;
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
  uint8_t collide_area_size = level.build_collide_area();

  for (uint8_t i = 0; i < collide_area_size; ++i) {
    if (area[i]->type == ENTITY_BLOCK) {
      Rect rect_block = area[i]->rect(), rect_ball = rect();

      if (arduboy.collide(rect_ball, rect_block)) {
        if (rect_ball.x > rect_block.x) {  // Left collision
          x = rect_block.x + rect_block.width;
          vel_x = -vel_x / 1.6;
        } else if (rect_ball.x < rect_block.x) {  // Right collision
          x = rect_block.x - rect_ball.width;
          vel_x = -vel_x / 1.6;
        }
      }
    } else if (area[i]->type == ENTITY_RAMP) {
      Rect rect_ramp = area[i]->rect(), rect_ball = rect();

      if (arduboy.collide(rect_ball, rect_ramp)) {
        int8_t h = min(rect_ramp.height, rect_ball.x + rect_ball.width - rect_ramp.x);
        if (rect_ball.y + rect_ball.height - rect_ramp.y > rect_ramp.height - h) {
          if (vel_x < 0) {
            x = rect_ramp.x + rect_ramp.width;
            vel_x = -vel_x / 1.6;
          } else if (vel_x > 0) {
            y = rect_ramp.y - h;
            vel_y = 0;
          }
        }
      }
    }
  }
};

void Ball::move_ver() {
  vel_y += BALL_AC_Y;
  y += vel_y;

  state |= BALL_STATE_JUMP;
};

void Ball::collide_ver() {
  uint8_t collide_area_size = level.build_collide_area();

  for (uint8_t i = 0; i < collide_area_size; ++i) {
    if (area[i]->type == ENTITY_BLOCK) {
      Rect rect_block = area[i]->rect(), rect_ball = rect();

      if (arduboy.collide(rect_ball, rect_block)) {
        if (vel_y < 0) {
          y = rect_block.y + rect_block.height;
          vel_y = 0;
        } else if (vel_y > 0) {
          state &= ~BALL_STATE_JUMP;
          y = rect_block.y - rect_ball.height;
          vel_y = -vel_y / 1.6;
        }
      }
    } else if (area[i]->type == ENTITY_RAMP) {
      Rect rect_ramp = area[i]->rect(), rect_ball = rect();

      if (arduboy.collide(rect_ball, rect_ramp)) {
        int8_t h = min(rect_ramp.height, rect_ball.x + rect_ball.width - rect_ramp.x);
        if (rect_ball.y + rect_ball.height - rect_ramp.y > rect_ramp.height - h) {
          if (vel_y < 0) {
            y = rect_ramp.y + rect_ramp.height;
            vel_y = 0;
          } else if (vel_y > 0) {
            state &= ~BALL_STATE_JUMP;
            y = rect_ramp.y - h;
            if (!vel_x && rect_ball.x <= rect_ramp.x) vel_x = -max(vel_y, 1.9) / 2;
            vel_y = 0;
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
