#pragma once

#include <Arduboy2.h>

#include "objects.h"

enum class BallRect : uint8_t {
  SMALL_RE_VER,
  SMALL_RE_HOR,
  SMALL_SQ,
  BIG_RE_VER_BG,
  BIG_RE_VER_SM,
  BIG_RE_HOR_BG,
  BIG_RE_HOR_SM,
  END_SEQ
};

const BallRect RECTS_SMALL_HOR[] PROGMEM = {
  BallRect::SMALL_RE_HOR, BallRect::SMALL_SQ, BallRect::END_SEQ
};
const BallRect RECTS_SMALL_VER[] PROGMEM = {
  BallRect::SMALL_RE_VER, BallRect::SMALL_SQ, BallRect::END_SEQ
};
const BallRect RECTS_BIG_HOR[] PROGMEM = {
  BallRect::BIG_RE_HOR_BG, BallRect::BIG_RE_HOR_SM, BallRect::END_SEQ
};
const BallRect RECTS_BIG_VER[] PROGMEM = {
  BallRect::BIG_RE_VER_BG, BallRect::BIG_RE_VER_SM, BallRect::END_SEQ
};

struct Ball {
  float x, y, velx, vely, acx;
  uint8_t lives;

  int16_t cx, cy;

  uint8_t state;
  const uint8_t *image;

  BallRect *rectType;

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

  bool _rectIter(Rect &rectBall, const BallRect *seq);
  void _adjustRect(Rect &rectBall);

  void _collideBlock(Rect &rectBall, Rect &rectBlock, bool isHor);
  void _collideBlockHor(Rect &rectBall, Rect &rectBlock);
  void _collideBlockVer(Rect &rectBall, Rect &rectBlock);
  void _processPop();

  void _collideRing(Rect &rectBall, Entity *ring, Rect &rectRing, bool isHor);
  void _collideCrys(Entity *crys);
  void _collideCrysBall(Entity *crysBall);
  bool _collideInflatorAndDeflator(Rect &rectBall, Rect &rectEntity, bool isInflator, bool isHor);
  bool _collideEnd(Rect &rectBall, Entity *end, Rect &rectEnd, bool isHor);
};

extern Ball ball;
