#include "level.h"

#include <Arduboy2.h>
#include <ArduboyFX.h>
#include <EEPROM.h>

#include "../assets/images.h"
#include "../assets/levels.h"
#include "../constants.h"
#include "ball.h"
#include "objects.h"
#include "scene.h"

extern Arduboy2 arduboy;
extern Sprites sprites;

Level level;
Entity *area[COLLIDE_AREA_SIZE];

void States::init() {
  size = 0;
};

uint16_t States::getKey(Entity *entity) {
  return (entity->y / 8 << 8) + entity->x / 8;
};

uint8_t States::get(Entity *entity) {
  uint16_t key = getKey(entity);

  for (uint8_t i = 0; i < size; ++i) {
    if (table[i].key == key) return table[i].value;
  }
  return 0;
};

void States::set(Entity *entity, uint8_t state) {
  uint16_t key = getKey(entity);
  table[size++] = {key, state};
}

void Level::init(uint8_t levelNo, uint32_t score) {
  this->levelNo = levelNo;
  this->score = score;

  horBound = 0;

  states.init();

  shiftX = 0;
  shiftY = -SURFACE_B_H;

  endX = (*this)[3];
  endY = (*this)[4];
  rings = (*this)[5];
  width = (*this)[6];
  height = (*this)[7];

  score = 0;
};

void Level::moveHor() {
  updateOffsets();

  int16_t nextShiftX = -offsetX / 8;
  int16_t hor = nextShiftX - shiftX;

  // Horizontal scrolling (right for ball)
  if (hor > 0) {
    shiftX -= min(0, SURFACE_B_W - hor);
    hor = min(hor, SURFACE_B_W);
  }
  for (; hor > 0; --hor) {
    ++shiftX;

    for (uint8_t i = 0; i < SURFACE_B_H; ++i)
      loadEntity(entities[i][horBound], shiftX + SURFACE_B_W - 1, shiftY + i);

    ++horBound;
    if (horBound == SURFACE_B_W) horBound = 0;
  }

  // Horizontal scrolling (left for ball)
  if (hor < 0) {
    shiftX += min(0, SURFACE_B_W + hor);
    hor = max(hor, -SURFACE_B_W);
  }
  for (; hor < 0; ++hor) {
    --shiftX;

    --horBound;
    if (horBound == -1) horBound += SURFACE_B_W;

    for (uint8_t i = 0; i < SURFACE_B_H; ++i)
      loadEntity(entities[i][horBound], shiftX, shiftY + i);
  }
};

void Level::updateOffsets() {
  int16_t ballCenterX = round(ball.x) + pgm_read_byte(&ball.image[0]) / 2.;

  offsetX = 0;
  if (ballCenterX > SURFACE_W / 2) {
    offsetX = max(SURFACE_W / 2 - ballCenterX, SURFACE_W - width * 8);
  }

  offsetY = -shiftY * 8;
}

void Level::moveVer() {
  int16_t nextShiftY = round(ball.y) / 8 / 7 * 7;
  int16_t ver = nextShiftY - shiftY;

  if (!ver) return;

  // Vertical scrolling (up/down for ball)
  shiftY += ver;

  for (uint8_t i = 0; i < SURFACE_B_H; ++i)
    for (uint8_t j = 0; j < SURFACE_B_W; ++j)
      loadEntity(entities[i][j], shiftX + j, shiftY + i);

  horBound = 0;
};

uint8_t Level::translateCol(uint8_t j) {
  uint8_t col = j + horBound;
  if (col >= SURFACE_B_W) col -= SURFACE_B_W;
  return col;
};

uint8_t Level::buildCollideArea() {
  Rect rectBall = ball.rect();
  int8_t centerx = (rectBall.x + rectBall.width / 2) / 8 - shiftX,
         centery = (rectBall.y + rectBall.height / 2) / 8 - shiftY;

  uint8_t collideAreaSize = 0;
  for (uint8_t k = max(0, centerx - 1); k <= min(SURFACE_B_W - 1, centerx + 1); ++k) {
    uint8_t j = translateCol(k);
    for (uint8_t i = max(0, centery - 1); i <= min(SURFACE_B_H - 1, centery + 1); ++i) {
      area[collideAreaSize] = &entities[i][j];
      ++collideAreaSize;
    }
  }

  for (uint8_t i = 1; i < COLLIDE_AREA_SIZE; ++i) {  // Insertion sort
    Entity *tmp = area[i];
    int8_t j = i - 1;
    for (; j >= 0 && area[j]->type > tmp->type; --j) {
      area[j + 1] = area[j];
    }
    area[j + 1] = tmp;
  }
  return collideAreaSize;
};

void Level::drawSurface() {
  for (uint8_t k = 0; k < SURFACE_B_W; ++k) {
    uint8_t j = translateCol(k);
    for (uint8_t i = 0; i < SURFACE_B_H; ++i) {
      if (entities[i][j].type != ENTITY_EMPTY) {
        sprites.drawOverwrite(
          offsetX + SURFACE_X + entities[i][j].x, offsetY + entities[i][j].y, entities[i][j].image,
          states.get(&entities[i][j])
        );
      }
    }
  }
};

void Level::drawInterface() {
  arduboy.setTextColor(BLACK);

  // Draw rings info
  arduboy.setCursor(1, 2);
  arduboy.print(rings);
  arduboy.print(F("x"));
  sprites.drawOverwrite(13, 1, IMAGE_RING_INFO, 0);

  // Draw ball info
  arduboy.setCursor(1, 11);
  arduboy.print(ball.lives);
  arduboy.print(F("x"));
  sprites.drawOverwrite(13, 10, IMAGE_BALL_INFO, 0);

  // Draw score
  uint32_t d = 1;

  for (uint8_t i = 0; i < 8; ++i)
    d *= 10;

  for (uint8_t i = 0; i < 9; ++i, d /= 10) {
    sprites.drawOverwrite(
      SCREEN_W - SURFACE_X + 9, 5 + i * 6, IMAGE_ROTATED_DIGITS, score / d % 10
    );
  }
};

uint8_t Level::operator[](uint16_t i) {
  uint8_t b;

  FX::disableOLED();
  FX::readDataBytes(LEVELS[levelNo] + i, &b, 1);
  FX::enableOLED();

  return b;
}
