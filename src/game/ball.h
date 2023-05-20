#pragma once

#include <Arduboy2Ex.h>

struct Ball {
  float x, y, velx, vely, acx;
  uint8_t lives;

  int16_t cx, cy;

  uint8_t state;
  const uint8_t *image;

  Ball() = default;
  void init(int16_t x, int16_t y, uint8_t lives);

  void reset();

  void checkEvents();

  void moveHor();
  void collideHor();

  void moveVer();
  void collideVer();

  void draw();

  Rect rect();

  void _collideBlockHor(Rect &rectBall, Rect &rectBlock);
  void _processPop();
};

extern Ball ball;
