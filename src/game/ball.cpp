#include "ball.h"

#include <Arduboy2Ex.h>

#include "../assets/images.h"
#include "../constants.h"
#include "../scenes.h"
#include "objects.h"
#include "scene.h"

extern Arduboy2Ex arduboy;
extern Sprites sprites;

Ball ball;

Ball::Ball(int16_t x, int16_t y) {
  image = IMAGE_BALL;
  vel_x = vel_y = ac_x = 0;
  this->x = x;
  this->y = y;
};

void Ball::check_events() {
  uint8_t state = arduboy.buttonsState();

  if (state & B_BUTTON) scene = Scene::BOUNCE;

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

void Ball::_collide_block_hor(Rect &rect_ball, Rect &rect_block) {
  if (rect_ball.x > rect_block.x) {  // Left collision
    x = rect_block.x + rect_block.width;
    vel_x = -vel_x / 1.6;
  } else if (rect_ball.x < rect_block.x) {  // Right collision
    x = rect_block.x - rect_ball.width;
    vel_x = -vel_x / 1.6;
  }
};

void Ball::collide_hor() {
  uint8_t collide_area_size = level.build_collide_area();

  for (uint8_t i = 0; i < collide_area_size; ++i) {
    Rect rect_ball = rect(), rect_entity = area[i]->rect();

    if (!arduboy.collide(rect_ball, rect_entity)) continue;

    if (area[i]->type == ENTITY_BLOCK) {
      _collide_block_hor(rect_ball, rect_entity);
    } else if (area[i]->type == ENTITY_RAMP) {
      int8_t h = min(rect_entity.height, rect_ball.x + rect_ball.width - rect_entity.x);
      if (rect_ball.y + rect_ball.height - rect_entity.y > rect_entity.height - h) {
        if (vel_x < 0) {
          x = rect_entity.x + rect_entity.width;
          vel_x = -vel_x / 1.6;
        } else if (vel_x > 0) {
          y = rect_entity.y - h;
          vel_y = 0;
        }
      }
    } else if (area[i]->type >= ENTITY_RING_VER && area[i]->type <= ENTITY_RING_HOR) {
      if (!level.states.get(area[i])) {
        level.states.set(area[i], 1);
        --level.rings;
        if (!level.rings) {
          Entity entityEnd = Entity(level.endX * 8l, level.endY * 8l);
          level.states.set(&entityEnd, 1);
        }
      }
    } else if (area[i]->type == ENTITY_END) {
      if (level.states.get(area[i])) {
        // Todo
      } else {
        _collide_block_hor(rect_ball, rect_entity);
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
    Rect rect_ball = rect(), rect_entity = area[i]->rect();

    if (!arduboy.collide(rect_ball, rect_entity)) continue;

    if (area[i]->type == ENTITY_BLOCK) {
      if (vel_y < 0) {
        y = rect_entity.y + rect_entity.height;
        vel_y = 0;
      } else if (vel_y > 0) {
        state &= ~BALL_STATE_JUMP;
        y = rect_entity.y - rect_ball.height;
        vel_y = -vel_y / 1.6;
      }
    } else if (area[i]->type == ENTITY_RAMP) {
      int8_t h = min(rect_entity.height, rect_ball.x + rect_ball.width - rect_entity.x);
      if (rect_ball.y + rect_ball.height - rect_entity.y > rect_entity.height - h) {
        if (vel_y < 0) {
          y = rect_entity.y + rect_entity.height;
          vel_y = 0;
        } else if (vel_y > 0) {
          state &= ~BALL_STATE_JUMP;
          y = rect_entity.y - h;
          if (!vel_x && rect_ball.x <= rect_entity.x) vel_x = -max(vel_y, 1.9) / 2;
          vel_y = 0;
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
