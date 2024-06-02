#include "ball.h"

#include <Arduboy2.h>

#include "../assets/images.h"
#include "../constants.h"
#include "../scenes.h"
#include "objects.h"
#include "scene.h"
#include "spiders.h"

extern Arduboy2 arduboy;
extern Sprites sprites;

Ball ball;

void Ball::init(int16_t x, int16_t y, uint8_t lives) {
  image = IMAGE_BALL;
  velx = vely = acx = 0;
  this->lives = lives;
  this->x = cx = x;
  this->y = cy = y;
  state = 0;
  rectType = nullptr;
};

void Ball::reset() {
  init(cx, cy, lives - 1);
};

void Ball::checkEvents() {
  uint8_t state = arduboy.buttonsState();

  if (state & B_BUTTON) scene = Scene::BOUNCE;

  if (state & LEFT_BUTTON) acx = -BALL_AC_X;
  else if (state & RIGHT_BUTTON) acx = BALL_AC_X;
  else acx = 0;

  if (state & UP_BUTTON && !(this->state & BALL_STATE_JUMP)) {
    this->state |= BALL_STATE_JUMP;

    if (this->state & BALL_STATE_BIG) vely = -BALL_BIG_MAX_VEL_Y_UP;
    else vely = -BALL_MAX_VEL_Y;
  }
};

bool Ball::_rectIter(Rect &rectBall, const BallRect *seq) {
  if (rectType == nullptr) rectType = const_cast<BallRect *>(seq);
  else if (static_cast<BallRect>(pgm_read_byte(++rectType)) == BallRect::END_SEQ) {
    rectType = nullptr;
    return 0;
  }

  rectBall = rect();
  return 1;
}

Rect Ball::rect() {
  int32_t roundX = round(x), roundY = round(y);

  if (rectType == nullptr) goto default_rect;

  switch (static_cast<BallRect>(pgm_read_byte(rectType))) {
    case BallRect::SMALL_RE_VER:
      return Rect(roundX + 2, roundY, 4, 8);
    case BallRect::SMALL_RE_HOR:
      return Rect(roundX, roundY + 2, 8, 4);
    case BallRect::SMALL_SQ:
      return Rect(roundX + 1, roundY + 1, 6, 6);
    case BallRect::BIG_RE_VER_BG:
      return Rect(roundX + 3, roundY, 5, 11);
    case BallRect::BIG_RE_VER_SM:
      return Rect(roundX + 2, roundY + 1, 7, 9);
    case BallRect::BIG_RE_HOR_BG:
      return Rect(roundX, roundY + 3, 11, 5);
    case BallRect::BIG_RE_HOR_SM:
      return Rect(roundX + 1, roundY + 2, 9, 7);
    default:
      goto default_rect;
  }

default_rect:
  return Rect(roundX, roundY, pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
}

void Ball::_adjustRect(Rect &rectBall) {
  if (rectType == nullptr) return;

  Rect oldRectBall = rect();
  if (!memcmp(&oldRectBall, &rectBall, sizeof(Rect))) return;

  switch (static_cast<BallRect>(pgm_read_byte(rectType))) {
    case BallRect::SMALL_RE_VER: {
      x = rectBall.x - 2;
      y = rectBall.y;
      break;
    }
    case BallRect::SMALL_RE_HOR: {
      x = rectBall.x;
      y = rectBall.y - 2;
      break;
    }
    case BallRect::SMALL_SQ: {
      x = rectBall.x - 1;
      y = rectBall.y - 1;
      break;
    }
    case BallRect::BIG_RE_VER_BG: {
      x = rectBall.x - 3;
      y = rectBall.y;
      break;
    }
    case BallRect::BIG_RE_VER_SM: {
      x = rectBall.x - 2;
      y = rectBall.y - 1;
      break;
    }
    case BallRect::BIG_RE_HOR_BG: {
      x = rectBall.x;
      y = rectBall.y - 3;
      break;
    }
    case BallRect::BIG_RE_HOR_SM: {
      x = rectBall.x - 1;
      y = rectBall.y - 2;
      break;
    }
  }
}

void Ball::moveHor() {
  if (acx > 0) velx = min(BALL_MAX_VEL_X, velx + acx);
  else if (acx < 0) velx = max(-BALL_MAX_VEL_X, velx + acx);
  else {
    if (velx > 0) velx = max(0, velx - BALL_AC_X);
    else velx = min(0, velx + BALL_AC_X);
  }

  x += velx;
};

void Ball::_collideBlock(Rect &rectBall, Rect &rectBlock, bool isHor) {
  if (isHor) _collideBlockHor(rectBall, rectBlock);
  else _collideBlockVer(rectBall, rectBlock);
}

void Ball::_collideBlockHor(Rect &rectBall, Rect &rectBlock) {
  if (rectBall.x + rectBall.width / 2 > rectBlock.x + rectBlock.width / 2) {  // Left collision
    rectBall.x = rectBlock.x + rectBlock.width;
    velx = -velx / 1.6;
  } else {  // Right collision
    rectBall.x = rectBlock.x - rectBall.width;
    velx = -velx / 1.6;
  }
};

void Ball::_collideBlockVer(Rect &rectBall, Rect &rectBlock) {
  if (rectBall.y + rectBall.height / 2 > rectBlock.y + rectBlock.height / 2) {
    rectBall.y = rectBlock.y + rectBlock.height;
    vely = 0;
  } else {
    state &= ~BALL_STATE_JUMP;
    rectBall.y = rectBlock.y - rectBall.height;
    vely = -vely / 1.6;
  }
}

void Ball::_processPop() {
  if (!lives) scene = Scene::GAME_OVER;
  state |= BALL_STATE_POP;
  image = IMAGE_BALL_POP;
};

void Ball::collideHor() {
  Rect rectBall;

  while (_rectIter(rectBall, (state & BALL_STATE_BIG ? RECTS_BIG_HOR : RECTS_SMALL_HOR))) {
    uint8_t collideAreaSize = level.buildCollideArea();

    for (uint8_t i = 0; i < collideAreaSize; ++i) {
      Rect rectEntity = area[i]->rect();

      if (!arduboy.collide(rectBall, rectEntity)) continue;

      if (area[i]->type == ENTITY_BLOCK) {
        _collideBlockHor(rectBall, rectEntity);
      } else if (area[i]->type == ENTITY_RAMP_TL) {
        int8_t h = min(rectEntity.height, rectBall.x + rectBall.width - rectEntity.x);
        if (rectBall.y + rectBall.height - rectEntity.y > rectEntity.height - h && velx > 0) {
          rectBall.y = rectEntity.y + rectEntity.height - rectBall.height - h;
          vely = 0;
        }
      } else if (area[i]->type == ENTITY_RAMP_TR) {
        int8_t h = min(rectEntity.height, rectEntity.x + rectEntity.width - rectBall.x);
        if (rectBall.y + rectBall.height - rectEntity.y > rectEntity.height - h && velx < 0) {
          rectBall.y = rectEntity.y + rectEntity.height - rectBall.height - h;
          vely = 0;
        }
      } else if (area[i]->type >= ENTITY_RING_VER && area[i]->type <= ENTITY_BIG_RING_HOR) {
        _collideRing(rectBall, area[i], rectEntity, 1);
      } else if (area[i]->type == ENTITY_CRYS) {
        _collideCrys(area[i]);
      } else if (area[i]->type == ENTITY_CRYS_BALL) {
        _collideCrysBall(area[i]);
      } else if (area[i]->type >= ENTITY_SPIKE_DOWN && area[i]->type <= ENTITY_SPIKE_RIGHT) {
        _processPop();
        break;
      } else if (area[i]->type >= ENTITY_DEFLATOR_DOWN && area[i]->type <= ENTITY_DEFLATOR_RIGHT) {
        _collideBlockHor(rectBall, rectEntity);
      } else if (area[i]->type >= ENTITY_INFLATOR_DOWN && area[i]->type <= ENTITY_INFLATOR_RIGHT) {
        if (_collideInflator(rectBall, rectEntity, 1)) break;
      } else if (area[i]->type == ENTITY_END) {
        if (_collideEnd(rectBall, area[i], rectEntity, 1)) break;
      }
    }

    _adjustRect(rectBall);
  }
};

void Ball::moveVer() {
  if (state & BALL_STATE_BIG) {
    if (vely < 0) vely += BALL_BIG_AC_Y;
    else vely = min(vely + BALL_BIG_AC_Y, BALL_BIG_MAX_VEL_Y_DOWN);
  } else vely += BALL_AC_Y;

  y += vely;
  state |= BALL_STATE_JUMP;
};

void Ball::collideVer() {
  Rect rectBall;

  while (_rectIter(rectBall, (state & BALL_STATE_BIG ? RECTS_BIG_VER : RECTS_SMALL_VER))) {
    uint8_t collideAreaSize = level.buildCollideArea();

    for (uint8_t i = 0; i < collideAreaSize; ++i) {
      Rect rectEntity = area[i]->rect();

      if (!arduboy.collide(rectBall, rectEntity)) continue;

      if (area[i]->type == ENTITY_BLOCK) {
        _collideBlockVer(rectBall, rectEntity);
      } else if (area[i]->type == ENTITY_RAMP_TL) {
        int8_t h = min(rectEntity.height, rectBall.x + rectBall.width - rectEntity.x);
        if (rectBall.y + rectBall.height - rectEntity.y > rectEntity.height - h) {
          if (vely < 0) {
            rectBall.y = rectEntity.y + rectEntity.height;
            vely = 0;
          } else if (vely > 0) {
            state &= ~BALL_STATE_JUMP;
            rectBall.y = rectEntity.y + rectEntity.height - rectBall.height - h;
            if (!velx && rectBall.x + rectBall.width <= rectEntity.x + rectEntity.width)
              velx = -max(vely, 1.9) / 2;
            vely = 0;
          }
        }
      } else if (area[i]->type == ENTITY_RAMP_TR) {
        int8_t h = min(rectEntity.height, rectEntity.x + rectEntity.width - rectBall.x);
        if (rectBall.y + rectBall.height - rectEntity.y > rectEntity.height - h) {
          if (vely < 0) {
            rectBall.y = rectEntity.y + rectEntity.height;
            vely = 0;
          } else if (vely > 0) {
            state &= ~BALL_STATE_JUMP;
            rectBall.y = rectEntity.y + rectEntity.height - rectBall.height - h;
            if (!velx && rectBall.x >= rectEntity.x) velx = max(vely, 1.9) / 2;
            vely = 0;
          }
        }
      } else if (area[i]->type >= ENTITY_RING_VER && area[i]->type <= ENTITY_BIG_RING_HOR) {
        _collideRing(rectBall, area[i], rectEntity, 0);
      } else if (area[i]->type == ENTITY_CRYS) {
        _collideCrys(area[i]);
      } else if (area[i]->type == ENTITY_CRYS_BALL) {
        _collideCrysBall(area[i]);
      } else if (area[i]->type >= ENTITY_SPIKE_DOWN && area[i]->type <= ENTITY_SPIKE_RIGHT) {
        _processPop();
        break;
      } else if (area[i]->type >= ENTITY_DEFLATOR_DOWN && area[i]->type <= ENTITY_DEFLATOR_RIGHT) {
        _collideBlockVer(rectBall, rectEntity);
      } else if (area[i]->type >= ENTITY_INFLATOR_DOWN && area[i]->type <= ENTITY_INFLATOR_RIGHT) {
        if (_collideInflator(rectBall, rectEntity, 0)) break;
      } else if (area[i]->type == ENTITY_END) {
        if (_collideEnd(rectBall, area[i], rectEntity, 0)) break;
      }
    }

    _adjustRect(rectBall);
  }

  // Collide spiders
  rectBall = rect();
  for (Spider &spider : spiders) {
    Rect rectSpider = Rect(spider.getX(), spider.getY(), 16, 16);

    if (arduboy.collide(rectBall, rectSpider)) {
      _processPop();
      break;
    }
  }
};

void Ball::_collideRing(Rect &rectBall, Entity *ring, Rect &rectRing, bool isHor) {
  if (ring->type == ENTITY_RING_VER || ring->type == ENTITY_BIG_RING_VER) {
    Rect rectBorder = Rect(rectRing.x, rectRing.y, rectRing.width, 2);
    if (arduboy.collide(rectBall, rectBorder)) _collideBlock(rectBall, rectBorder, isHor);
  }

  if (ring->type == ENTITY_RING_HOR || ring->type == ENTITY_BIG_RING_HOR) {
    Rect rectLeftBorder = Rect(rectRing.x, rectRing.y, 2, rectRing.height),
         rectRightBorder = Rect(rectRing.x + rectRing.width - 2, rectRing.y, 2, rectRing.height);

    if (arduboy.collide(rectBall, rectLeftBorder)) _collideBlock(rectBall, rectLeftBorder, isHor);
    if (arduboy.collide(rectBall, rectRightBorder)) _collideBlock(rectBall, rectRightBorder, isHor);
  }

  if (!level.states.get(ring)) {
    level.states.set(ring, 1);
    --level.rings;
    level.score += SCORE_RING;

    if (!level.rings) {
      Entity entityEnd = Entity(level.endX * 8l, level.endY * 8l);
      level.states.set(&entityEnd, 1);
    }
  }
}

void Ball::_collideCrys(Entity *crys) {
  if (level.states.get(crys)) return;
  level.states.set(crys, 1);
  cx = crys->x;
  cy = crys->y;
  level.score += SCORE_CRYS;
}

void Ball::_collideCrysBall(Entity *crysBall) {
  if (level.states.get(crysBall)) return;
  level.states.set(crysBall, 1);
  lives = min(5, lives + 1);
  level.score += SCORE_CRYS_BALL;
}

bool Ball::_collideInflator(Rect &rectBall, Rect &rectInflator, bool isHor) {
  if (state & BALL_STATE_BIG) {
    _collideBlock(rectBall, rectInflator, isHor);
    return 0;
  }

  float centerX = rectBall.x + rectBall.width / 2., centerY = rectBall.y + rectBall.height / 2.;

  state |= BALL_STATE_BIG;
  image = IMAGE_BIG_BALL;
  x = centerX - 11 / 2.;
  y = centerY - 11 / 2.;

  // Re-run collision check with new rect model
  rectType = nullptr;
  return 1;
}

bool Ball::_collideEnd(Rect &rectBall, Entity *end, Rect &rectEnd, bool isHor) {
  if (level.states.get(end)) {
    scene = Scene::COMPLETED;
    level.score += SCORE_LEVEL_COMPLETED;
    return 1;
  }

  _collideBlock(rectBall, rectEnd, isHor);
  return 0;
}

void Ball::draw() {
  sprites.drawPlusMask(level.offsetX + SURFACE_X + round(x), level.offsetY + round(y), image, 0);
};
