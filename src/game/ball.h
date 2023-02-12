#pragma once

#include <Arduboy2Ex.h>

struct Ball {
  float x, y, velx, vely, acx;

  uint8_t state;
  const uint8_t *image;

  Ball() = default;
  Ball(int16_t x, int16_t y);

  void checkEvents();

  void moveHor();
  void collideHor();

  void moveVer();
  void collideVer();

  void draw();

  Rect rect();

  void _collideBlockHor(Rect &rectBall, Rect &rectBlock);
};

extern Ball ball;
