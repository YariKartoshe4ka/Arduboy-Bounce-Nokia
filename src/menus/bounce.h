#pragma once

#include <Arduboy2Ex.h>

#include "../assets/texts.h"
#include "../constants.h"
#include "menu.h"

const char* const BOUNCE_TEXT[] PROGMEM = {
  TEXT_BOUNCE, TEXT_NEW_GAME, TEXT_HIGH_SCORE, TEXT_INSTRUCTIONS};
const Scene BOUNCE_SCENES[] PROGMEM = {
  Scene::BOUNCE, Scene::NEW_GAME, Scene::HIGH_SCORE, Scene::INSTRUCTIONS};
static constexpr uint8_t BOUNCE_TEXT_SIZE = sizeof(BOUNCE_TEXT) / sizeof(BOUNCE_TEXT[0]);

const char* const PAUSE_TEXT[] PROGMEM = {
  TEXT_BOUNCE, TEXT_CONTINUE, TEXT_NEW_GAME, TEXT_HIGH_SCORE, TEXT_INSTRUCTIONS};
const Scene PAUSE_SCENES[] PROGMEM = {
  Scene::BOUNCE, Scene::GAME, Scene::NEW_GAME, Scene::HIGH_SCORE, Scene::INSTRUCTIONS};
static constexpr uint8_t PAUSE_TEXT_SIZE = sizeof(PAUSE_TEXT) / sizeof(PAUSE_TEXT[0]);

extern MenuOptions menuBounce;

void sceneInitBounce();
void sceneUpdateBounce();
