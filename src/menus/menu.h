#pragma once

#include <Arduboy2Ex.h>

typedef const __FlashStringHelper *FlashString;

class MenuBase {
 protected:
  bool justPressedOnce(uint8_t button);
  int8_t centerFString(char *str);

  void checkEvents();
  void drawTitle(char *title);

 public:
  char **text;
  uint8_t *scenes;

  MenuBase() = default;
  MenuBase(char **text, uint8_t *scenes) : text(text), scenes(scenes){};

  void sceneInit();
  void sceneUpdate();
};

class MenuOptions : public MenuBase {
 protected:
  uint8_t n, prevChoice = 0;

  void checkEvents();
  void choiceCallback();
  void drawOptions();

 public:
  uint8_t choice = 1;

  MenuOptions() = default;
  MenuOptions(uint8_t n, char **text, uint8_t *scenes) : MenuBase(text, scenes), n(n){};

  void sceneInit();
  void sceneUpdate();
};

class MenuScore : public MenuBase {
  uint32_t *score;

  void checkEvents();
  void drawScore();

 public:
  MenuScore() = default;
  MenuScore(char **text, uint8_t *scenes, uint32_t *score) : MenuBase(text, scenes), score(score){};

  void sceneInit();
  void sceneUpdate();
};
