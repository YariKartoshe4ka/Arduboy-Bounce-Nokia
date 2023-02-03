#pragma once

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char* const NEW_GAME_TEXT[] PROGMEM = {  //
  TEXT_NEW_GAME, TEXT_LEVEL_1, TEXT_LEVEL_2, TEXT_LEVEL_3,
  TEXT_LEVEL_4,  TEXT_LEVEL_5, TEXT_LEVEL_6, TEXT_LEVEL_7};
const Scene NEW_GAME_SCENES[] PROGMEM = {  //
  Scene::BOUNCE, Scene::GAME, Scene::GAME, Scene::GAME,
  Scene::GAME,   Scene::GAME, Scene::GAME, Scene::GAME};

extern MenuOptions menuNewGame;

void sceneInitNewGame();
void sceneUpdateNewGame();
