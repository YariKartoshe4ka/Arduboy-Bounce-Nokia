#include "constants.h"
#include "game/scene.h"

typedef void (*funcptr)();

static uint8_t scene = SCENE_GAME;
static uint8_t prev_scene = SCENE_NULL;

static funcptr scenes_init[] = {scene_init_game};
static funcptr scenes_update[] = {scene_update_game};
