#pragma once

#include <Arduboy2.h>

#include "../constants.h"
#include "objects.h"

class States {
  struct {
    uint16_t key;
    uint8_t value;
  } table[STATES_TABLE_SIZE];

  uint8_t size;

  uint16_t getKey(Entity *entity);

 public:
  States() = default;
  void init();

  uint8_t get(Entity *entity);
  void set(Entity *entity, uint8_t state);
};

class Level {
  Entity entities[SURFACE_B_H][SURFACE_B_W];

  int8_t horBound;  // Free bound, if level moves left

 public:
  States states;

  uint8_t levelNo;  // Level number

  /* Meta vars */
  uint8_t endX, endY, rings, width, height;

  int16_t offsetX, offsetY,
    shiftX,  // Blocks between left level side and surface
    shiftY;  // Blocks between top level sise and surface

  uint32_t score;

  Level() = default;
  void init(uint8_t levelNo, uint32_t score);

  void updateOffsets();
  uint8_t translateCol(uint8_t j);
  uint8_t buildCollideArea();
  void moveHor();
  void moveVer();
  void drawSurface();
  void drawInterface();

  uint8_t operator[](uint16_t i);
};

extern Level level;
extern Entity *area[COLLIDE_AREA_SIZE];
extern uint32_t highScore;
