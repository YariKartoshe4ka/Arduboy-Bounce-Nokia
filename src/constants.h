#pragma once

#include <Arduboy2.h>

/* Font constants */
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8
#define CHAR_SPACING 1

/* menu.h */
#define LINE_SPACING 2
#define TITLE_OFFSET_Y (CHAR_HEIGHT + LINE_SPACING * 3 + 1)

/* bounce.ino */
#define FPS 30

#define SCREEN_W 128
#define SCREEN_H 64

/* scenes.h */
enum class Scene : uint8_t {
  BOUNCE,
  NEW_GAME,
  HIGH_SCORE,
  INSTRUCTIONS,
  GAME,
  GAME_OVER,
  COMPLETED,
  DUMMY
};

/* game */

#define SURFACE_W 84
#define SURFACE_H SCREEN_H
#define SURFACE_X 22

#define SURFACE_B_W 12  // Amount of blocks in width
#define SURFACE_B_H 8   // Amount of blocks in height

/* objects.h */
#define BALL_AC_X .3
#define BALL_AC_Y .3
#define BALL_MAX_VEL_X 2.5
#define BALL_MAX_VEL_Y 4.6

#define BALL_STATE_BIG (1 << 0)
#define BALL_STATE_JUMP (1 << 1)
#define BALL_STATE_POP (1 << 2)

/* level.h */
#define COLLIDE_AREA_SIZE 9
#define STATES_TABLE_SIZE 50

/* score */
#define SCORE_RING 50
#define SCORE_CRYS 20
#define SCORE_CRYS_BALL 100
#define SCORE_LEVEL_COMPLETED 500

/* EEPROM */
#define EEPROM_BASE (EEPROM_STORAGE_SPACE_START + 0x10)
#define EEPROM_HIGH_SCORE (EEPROM_BASE)
