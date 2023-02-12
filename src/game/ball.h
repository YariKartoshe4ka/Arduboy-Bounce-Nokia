#pragma once

#include <Arduboy2Ex.h>

struct Ball {
  float x, y, vel_x, vel_y, ac_x;

  uint8_t state;
  const uint8_t *image;

  Ball() = default;
  Ball(int16_t x, int16_t y);

  void check_events();

  void move_hor();
  void collide_hor();

  void move_ver();
  void collide_ver();

  void draw();

  Rect rect();

  void _collide_block_hor(Rect &rect_ball, Rect &rect_block);
};

extern Ball ball;
