#include <Arduboy2.h>
#include "objects.h"


extern Arduboy2 arduboy;
extern Entity entities[SURFACE_B_H][SURFACE_B_W];


Entity::Entity() {};
Entity::Entity(int16_t x, int16_t y) {
  type = ENTITY_EMPTY;
  this->x = x;
  this->y = y;
};

Block::Block(int16_t x, int16_t y) {
  type = ENTITY_BLOCK;
  image = IMAGE_BLOCK;
  this->x = x;
  this->y = y;
};


Ball::Ball () {};
Ball::Ball(int16_t x, int16_t y) {
  image = IMAGE_BALL;
  vel_x = vel_y = ac_x = ac_y = 0;
  this->x = x;
  this->y = y;
};

void Ball::check_events() {
  uint8_t state = arduboy.buttonsState();

  if (state & LEFT_BUTTON)
    ac_x = -BALL_AC_X;
  else if (state & RIGHT_BUTTON)
    ac_x = BALL_AC_X;
  else
    ac_x = 0;

  if (state & UP_BUTTON && !(this->state & BALL_STATE_JUMP)) {
    vel_y = -BALL_MAX_VEL_Y;
  }
};

void Ball::update() {
  // Horizontal movement
  if (ac_x > 0)
    vel_x = min(BALL_MAX_VEL_X, vel_x + ac_x);
  else if (ac_x < 0)
    vel_x = max(-BALL_MAX_VEL_X, vel_x + ac_x);
  else {
    if (vel_x > 0) vel_x = max(0, vel_x - BALL_AC_X);
    else vel_x = min(0, vel_x + BALL_AC_X);
  }

  x += vel_x;

  // Horizontal collisions
  for (int8_t i = 0; i < SURFACE_B_H; ++i) {
    for (int8_t j = 0; j < SURFACE_B_W; ++j) {
      if (entities[i][j].type == ENTITY_BLOCK) {
        Rect rect_block = RECT_ENTITY(entities[i][j]);
        Rect rect_ball = Rect(
          round(x),
          round(y),
          pgm_read_byte(&image[0]),
          pgm_read_byte(&image[1])
        );

        if (arduboy.collide(rect_ball, rect_block)) {
          if (rect_ball.x > rect_block.x) {
            x = rect_block.x + rect_block.width;
            vel_x = -vel_x / 1.6;
          }
          else if (rect_ball.x < rect_block.x) {
            x = rect_block.x - rect_ball.width;
            vel_x = -vel_x / 1.6;
          }
        }
      }
    }
  }

  // Vertical movement
  vel_y += BALL_AC_Y;
  y += vel_y;

  if (vel_y < 0)
    state |= BALL_STATE_JUMP;

  // Vertical collisions
  for (int8_t i = 0; i < SURFACE_B_H; ++i) {
    for (int8_t j = 0; j < SURFACE_B_W; ++j) {
      if (entities[i][j].type == ENTITY_BLOCK) {
        Rect rect_block = RECT_ENTITY(entities[i][j]);
        Rect rect_ball = Rect(
          round(x),
          round(y),
          pgm_read_byte(&image[0]),
          pgm_read_byte(&image[1])
        );

        if (arduboy.collide(rect_ball, rect_block)) {
          if (rect_ball.y > rect_block.y) {
            y = rect_block.y + rect_block.height;
            vel_y = 0;
          }
          else if (rect_ball.y < rect_block.y) {
            y = rect_block.y - rect_ball.height;
            state &= ~BALL_STATE_JUMP;
            vel_y = -vel_y / 1.6;
          }
        }
      }
    }
  }
};

float Ball::centerx() {
  return x + pgm_read_byte(&image[0]) / 2.;
};
