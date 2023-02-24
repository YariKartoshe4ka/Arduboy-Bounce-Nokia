#pragma once

#include <Arduboy2Ex.h>

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
  States();

  uint8_t get(Entity *entity);
  void set(Entity *entity, uint8_t state);
};

class Level {
 private:
  Entity entities[SURFACE_B_H][SURFACE_B_W];

  uint8_t levelNo,  // Level number
    width,          // Level width in blocks
    height;         // Level height in blocks

  int8_t horBound = 0;  // Free bound, if level moves left

  uint8_t *rle;
  uint16_t rlei;

 public:
  States states;

  /* Meta vars */
  uint8_t endX, endY, rings;

  int16_t offsetX, offsetY,
    shiftX,  // Blocks between left level side and surface
    shiftY;  // Blocks between top level sise and surface

  uint32_t score;

  Level() = default;
  Level(uint8_t levelNo);

  void loadEntity(uint8_t toi, uint8_t toj, uint16_t fromi, uint16_t fromj);
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
