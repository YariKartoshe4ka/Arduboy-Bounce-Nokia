#pragma once

/* bounce.ino */
#define FPS 30

#define SCREEN_W 128
#define SCREEN_H 64

/* scenes.h */
#define SCENE_BOUNCE 0
#define SCENE_GAME 1
#define SCENE_NULL 255

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

/* level.h */
#define COLLIDE_AREA_SIZE 9
