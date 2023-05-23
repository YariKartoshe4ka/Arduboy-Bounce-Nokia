#pragma once

#include <Arduboy2Ex.h>

void storageInit();
void storageUpdateHighScore(uint32_t highScore);

extern uint32_t storage_highScore;
