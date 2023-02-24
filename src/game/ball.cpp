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

Ball::Ball(int16_t x, int16_t y, uint8_t lives = 3) {
  image = IMAGE_BALL;
  velx = vely = acx = 0;
  this->lives = lives;
  this->x = cx = x;
  this->y = cy = y;
};

void Ball::reset() {
  state &= BALL_STATE_BIG;
  ball = Ball(cx, cy, lives - 1);
};

void Ball::checkEvents() {
  uint8_t state = arduboy.buttonsState();

  if (state & B_BUTTON) scene = Scene::BOUNCE;

  if (state & LEFT_BUTTON) acx = -BALL_AC_X;
  else if (state & RIGHT_BUTTON) acx = BALL_AC_X;
  else acx = 0;

  if (state & UP_BUTTON && !(this->state & BALL_STATE_JUMP)) {
    state |= BALL_STATE_JUMP;
    vely = -BALL_MAX_VEL_Y;
  }
};

void Ball::moveHor() {
  if (acx > 0) velx = min(BALL_MAX_VEL_X, velx + acx);
  else if (acx < 0) velx = max(-BALL_MAX_VEL_X, velx + acx);
  else {
    if (velx > 0) velx = max(0, velx - BALL_AC_X);
    else velx = min(0, velx + BALL_AC_X);
  }

  x += velx;
};

void Ball::_collideBlockHor(Rect &rectBall, Rect &rectBlock) {
  if (rectBall.x > rectBlock.x) {  // Left collision
    x = rectBlock.x + rectBlock.width;
    velx = -velx / 1.6;
  } else if (rectBall.x < rectBlock.x) {  // Right collision
    x = rectBlock.x - rectBall.width;
    velx = -velx / 1.6;
  }
};

void Ball::_processPop() {
  if (!lives) scene = Scene::GAME_OVER;
  state |= BALL_STATE_POP;
  image = IMAGE_BALL_POP;
}

void Ball::collideHor() {
  uint8_t collideAreaSize = level.buildCollideArea();

  for (uint8_t i = 0; i < collideAreaSize; ++i) {
    Rect rectBall = rect(), rectEntity = area[i]->rect();

    if (!arduboy.collide(rectBall, rectEntity)) continue;

    if (area[i]->type == ENTITY_BLOCK) {
      _collideBlockHor(rectBall, rectEntity);
    } else if (area[i]->type == ENTITY_RAMP) {
      int8_t h = min(rectEntity.height, rectBall.x + rectBall.width - rectEntity.x);
      if (rectBall.y + rectBall.height - rectEntity.y > rectEntity.height - h) {
        if (velx < 0) {
          x = rectEntity.x + rectEntity.width;
          velx = -velx / 1.6;
        } else if (velx > 0) {
          y = rectEntity.y - h;
          vely = 0;
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
    } else if (area[i]->type == ENTITY_CRYS && !level.states.get(area[i])) {
      level.states.set(area[i], 1);
      cx = area[i]->x;
      cy = area[i]->y;
    } else if (area[i]->type == ENTITY_SPIKE) {
      _processPop();
    } else if (area[i]->type == ENTITY_END) {
      if (level.states.get(area[i])) {
        // Todo
      } else {
        _collideBlockHor(rectBall, rectEntity);
      }
    }
  }
};

void Ball::moveVer() {
  vely += BALL_AC_Y;
  y += vely;

  state |= BALL_STATE_JUMP;
};

void Ball::collideVer() {
  uint8_t collideAreaSize = level.buildCollideArea();

  for (uint8_t i = 0; i < collideAreaSize; ++i) {
    Rect rectBall = rect(), rectEntity = area[i]->rect();

    if (!arduboy.collide(rectBall, rectEntity)) continue;

    if (area[i]->type == ENTITY_BLOCK) {
      if (vely < 0) {
        y = rectEntity.y + rectEntity.height;
        vely = 0;
      } else if (vely > 0) {
        state &= ~BALL_STATE_JUMP;
        y = rectEntity.y - rectBall.height;
        vely = -vely / 1.6;
      }
    } else if (area[i]->type == ENTITY_RAMP) {
      int8_t h = min(rectEntity.height, rectBall.x + rectBall.width - rectEntity.x);
      if (rectBall.y + rectBall.height - rectEntity.y > rectEntity.height - h) {
        if (vely < 0) {
          y = rectEntity.y + rectEntity.height;
          vely = 0;
        } else if (vely > 0) {
          state &= ~BALL_STATE_JUMP;
          y = rectEntity.y - h;
          if (!velx && rectBall.x <= rectEntity.x) velx = -max(vely, 1.9) / 2;
          vely = 0;
        }
      }
    } else if (area[i]->type == ENTITY_SPIKE) {
      _processPop();
    } else if (area[i]->type == ENTITY_END) {
      if (level.states.get(area[i])) {
        // Todo
      } else {
        // Todo
        // _collideBlockVer(rectBall, rectEntity);
      }
    }
  }
};

void Ball::draw() {
  sprites.drawPlusMask(level.offsetX + SURFACE_X + round(x), level.offsetY + round(y), image, 0);
};

Rect Ball::rect() {
  return Rect(round(x), round(y), pgm_read_byte(&image[0]), pgm_read_byte(&image[1]));
};
