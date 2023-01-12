#pragma once

#include <Arduboy2Ex.h>

typedef const __FlashStringHelper *FlashString;

class MenuBase {
 protected:
  char **text;
  uint8_t *scenes;

  bool justPressedOnce(uint8_t button);
  int8_t centerFString(const char *str);

  void checkEvents();
  void drawTitle();

 public:
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
