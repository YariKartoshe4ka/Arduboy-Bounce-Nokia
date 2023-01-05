#include "ball.h"

#include <Arduboy2.h>

#include "constants.h"
#include "level.h"
#include "objects.h"

extern Arduboy2 arduboy;
extern Entity *area[COLLIDE_AREA_SIZE];
extern Level level;
extern Sprites sprites;
extern uint8_t collide_area_size;

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
  level.build_collide_area();

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
    } else if (area[i]->type == ENTITY_STAIR) {
      Rect rect_stair = area[i]->rect(), rect_ball = rect();

      if (arduboy.collide(rect_ball, rect_stair)) {
        int8_t h = min(rect_stair.height, rect_ball.x + rect_ball.width - rect_stair.x);
        if (rect_ball.y + rect_ball.height - rect_stair.y > rect_stair.height - h) {
          if (vel_x < 0) {
            x = rect_stair.x + rect_stair.width;
            vel_x = -vel_x / 1.6;
          } else if (vel_x > 0) {
            y = rect_stair.y - h;
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
  level.build_collide_area();

  for (uint8_t i = 0; i < collide_area_size; ++i) {
    if (area[i]->type == ENTITY_BLOCK && !(state & BALL_STATE_ON_STAIR)) {
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
    } else if (area[i]->type == ENTITY_STAIR) {
      Rect rect_stair = area[i]->rect(), rect_ball = rect();

      if (arduboy.collide(rect_ball, rect_stair)) {
        int8_t h = min(rect_stair.height, rect_ball.x + rect_ball.width - rect_stair.x);
        if (rect_ball.y + rect_ball.height - rect_stair.y > rect_stair.height - h) {
          if (vel_y < 0) {
            y = rect_stair.y + rect_stair.height;
            vel_y = 0;
          } else if (vel_y > 0) {
            state &= ~BALL_STATE_JUMP;
            y = rect_stair.y - h;
            if (!vel_x && rect_ball.x <= rect_stair.x) vel_x = -max(vel_y, 1.1) / 1.6;
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
