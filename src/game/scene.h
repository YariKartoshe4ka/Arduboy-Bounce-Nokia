#pragma once

#include "../constants.h"
#include "ball.h"
#include "level.h"
#include "objects.h"

extern Ball ball;
extern Entity *area[COLLIDE_AREA_SIZE];

void scene_init_game();
void scene_update_game();
